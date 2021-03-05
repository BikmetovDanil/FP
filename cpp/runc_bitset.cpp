#include <iostream>
#include <vector>
#include <set>
#include <time.h>
#include <string>
#include <iomanip>
#include <chrono>
#include <bitset>



using namespace std;
const int m = 30, n = 50;
using TBitRow = std::bitset<n>;
using TBitCol = std::bitset<m>;

struct TMatrix
{
    vector<TBitRow> row_mat = vector<TBitRow>(m);
    vector<TBitCol> col_mat = vector<TBitCol>(n);
};

void Print(const vector<TBitRow>& ans) {
    for (size_t idx = 0; idx < ans.size(); ++idx) {
        for (int i = 0; i < n; ++i) {
            if (ans[idx][i]) {
                cout << i << ' ';
            }
        }
        cout << endl;
    }
}
class ISolver {
protected:
    int M, N;
    struct TContext {
        TContext()
            : S(n)
            {}

        TBitCol R;
        TBitRow D, H;
        vector<TBitCol> S;
    } Context;

    vector<size_t> Count;
    TMatrix Mat;

public:
    ISolver(TMatrix mat)
        : M(m)
        , N(n)
        , Context()
        , Mat(mat)
    {
        for (size_t i = 0; i < M; ++i) {
            Context.R.set(i);
            Count.push_back(Mat.row_mat[i].count());
        }
        for (size_t j = 0; j < N; ++j) {
            Context.D.set(j);
        }
    }

    virtual vector<TBitRow> solve() = 0;
};

class SmartSolver : public ISolver {
    void FillS(size_t j) {
        Context.S[j] = Context.R & Mat.col_mat[j];
    }

    size_t GetWithMinWeight() {
        ssize_t minIdx = -1;
        for (size_t idx = 0; idx < m; ++idx) {
            if (Context.R[idx]) {
                if (minIdx == -1) {
                    minIdx = idx;
                } else if (Count[idx] < Count[minIdx]) {
                    minIdx = idx;
                }
            }
        }
        return minIdx;
    }
    
    void BuildSubtreeRUNC(vector<TBitRow>& ans) {
        size_t i = GetWithMinWeight();
        for (size_t colIdx = 0; colIdx < n; ++colIdx) {
            if (!(Context.D[colIdx] && Mat.row_mat[i][colIdx])) {
                continue;
            }
            Context.D.reset(colIdx);
            TContext savedContext(Context);
            CreateNodeRUNC(colIdx);
            if (Context.R.count() == 0) {
                ans.emplace_back(std::move(Context.H));
            } else {
                BuildSubtreeRUNC(ans);
            }
            Context = std::move(savedContext);
        }
    }

    void CreateNodeRUNC(size_t j) {
        FillS(j);
        
        Context.R ^= Context.S[j]; // ~(R && MatCol[j])
        
        Context.H.set(j);

        if (Context.R.count() == 0) {
            return;
        }
        for (size_t coveredCol = 0; coveredCol < n; ++coveredCol) {
            if (!Context.H[coveredCol]) {
                continue;
            }
            if (Context.S[coveredCol].count() == 0) {
                continue;
            }
            if (coveredCol != j) {
                Context.S[coveredCol] &= ~Mat.col_mat[j];
            }

            //maybe faster with this
            /*bool needContinue = false;
            
            for (size_t row = 0; row < m; ++row) {
                if (Context.S[coveredCol][row] &&
                    ((Mat.row_mat[row] & Context.D).count() == 0)) {
                    Context.S[coveredCol] = 0;
                    needContinue = true;
                    break;
                }
            }
            if (needContinue) {
                continue;
            }*/
            if (Context.D.count() == 0) {
                return;
            }
            for (size_t colIdx = 0; colIdx < n; ++colIdx) {
                if (!Context.D[colIdx]) {
                    continue;
                }
                if ((Context.S[coveredCol] & Mat.col_mat[colIdx]) == Context.S[coveredCol]) {
                    Context.D.reset(colIdx);
                }
            }
        }
    }

public:
    SmartSolver(TMatrix str) : ISolver(str) {}

    vector<TBitRow> solve() override {
        vector<TBitRow> ans;
        BuildSubtreeRUNC(ans);
        return ans;
    }
};

class StupidSolver : public ISolver {
private:

    bool CheckCovered(long long mask) {
        vector<bool> checkRow(M);
        size_t colIdx = 0;
        while (mask) {
            if (mask & 1) {
                for (size_t rowIdx = 0; rowIdx < M; ++rowIdx) {
                    checkRow[rowIdx] = checkRow[rowIdx] || Mat.row_mat[rowIdx][colIdx];
                }
            }
            mask >>= 1;
            ++colIdx;
        }
        return std::all_of(checkRow.begin(), checkRow.end(), [](const auto& check) {return check == true;});
    }

    vector<long long> GenerateSubmasks(long long mask) {
        vector<long long> submasks;
        for (long long bit = 1; bit <= mask; bit <<= 1) {
            if (mask & bit) {
                submasks.push_back(mask ^ bit);
            }
        }
        return submasks;
    }

    TBitRow MakeCoverage(long long mask) {
        TBitRow s;
        size_t idx = 0;
        while (mask) {
            if (mask & 1) {
                s.set(idx);
            }
            mask >>= 1;
            ++idx;
        }
        return s;
    }

public:
    StupidSolver(TMatrix mat) : ISolver(mat) {}

    vector<TBitRow> solve() override {
        vector<TBitRow> ans;
        for (int mask = 1; mask < (1 << N); ++mask) {
            if (!CheckCovered(mask)) {
                continue;
            }
            auto submasks = GenerateSubmasks(mask);
            if (!std::none_of(submasks.begin(), submasks.end(), [this](const long long submask) {return CheckCovered(submask);})) {
                continue;
            }
            ans.push_back(MakeCoverage(mask));
        }
        return ans;
    }
};



string GenerateStringFromCoverages(const vector<TBitRow>& ans) {
    set<string> all;
    for (const auto& coverage : ans) {
        string coverageStr;
        
        for (size_t x = 0; x < n; ++x) {
            if (coverage[x]) {
                coverageStr += (to_string(x) + " ");
            }
        }
        all.insert(std::move(coverageStr));
    }
    string result;
    for (auto coverageStr : all) {
        result += "#" + coverageStr;
    }
    return result;
}


vector<TMatrix> GenerateInput() {
    int count = 10;

    vector<TMatrix> res;
    while(count--) {
        bool bad = false;
        vector<std::bitset<n>> row_mat(m);
        vector<std::bitset<m>> col_mat(n);
        for (int i = 0; i < m; ++i) {
            row_mat[i] = std::bitset<n>(0);
        }
        for (int j = 0; j < n; ++j) {
            col_mat[j] = std::bitset<m>(0);
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rand() % 2) {
                    row_mat[i].set(j);
                    col_mat[j].set(i);
                }
            }
            if (row_mat[i].count() == 0) {
                bad = true;
            }
        }
        if (bad) {
            ++count;
            continue;
        }
        TMatrix now = {row_mat, col_mat};
        res.push_back(std::move(now));
        }

    return res;
}

int main() {
    vector<TMatrix> input = GenerateInput();

    std::chrono::nanoseconds total;
    for (const auto& mat : input) {
        //cout << "Matrix:\n";
        /*for (const auto& row : mat) {
            cout << row << '\n';
        }*/
        SmartSolver smart(mat);
        auto start = std::chrono::system_clock::now();
        smart.solve();
        auto end = std::chrono::system_clock::now();
        total += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        //cout << "ok" << endl;
        /*string smartAns = GenerateStringFromCoverages(smart.solve());
        StupidSolver stupid(mat);
        string stupidAns = GenerateStringFromCoverages(stupid.solve());
        if (smartAns != stupidAns) {
            cout << "Error" << endl;
            
            cout << smartAns << endl;
            cout << stupidAns << endl;
            break;
        } else {
            cout << "OK" << endl;
        }*/
    }
    total /= input.size();
    auto milliseconds = total / 1'000'000;
    cout << setprecision(10) << total.count() / 1'000'000'000. << endl << milliseconds.count() / 1'000. << endl;

}
