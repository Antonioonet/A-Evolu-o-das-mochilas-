
#include <bits/stdc++.h>
using namespace std;
#define LOCAL
typedef long long ll;
typedef pair<int, int> pii;
typedef long double ld;

const ll maxn = 2e3 + 10;
const ll inf = LLONG_MAX;

#define pb push_back
#define ppb pop_back 
#define ff first
#define ss second 
#define sza(x) ((int)(x).size())
#define all(a) (a).begin(), (a).end()

#define FF(i, n) for(int i = 0; i < (n); i++)
#define FF1(i, n) for(int i = 1; i <= (n); i++)
#define FFZ(i, v) FF(i, sza(v))
#define F(n) FF(i, n)
#define F1(n) FF1(i, n)
#define FZ(v) FFZ(i, v)
#define smin(a,b) a = min(a,b)
#define smax(a,b) a = max(a,b)
#define weight ff
#define value ss

#define vi vector <int> 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.ff << ", " << p.ss << ")"; }

#ifdef LOCAL
void dbg_out() { cerr << endl; }
template<typename H, typename... T> void dbg_out(H h, T... t) { cerr << " " << h; dbg_out(t...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int PS = 1000;
const double MR = 0.001;
const int K = 100000;
const int N = 1000;

vector <pii> item;
int dp[(int)1e3  + 7][100007];
ll solve_dp() {
    
    memset(dp,0,sizeof(dp));

    F(N){
        smax(dp[i+1][item[i].ff],item[i].ss); 
        FF1(j,K){
            if(dp[i][j]){
                smax(dp[i+1][j],dp[i][j]);
                if(j + item[i].ff <= K){ 
                    smax(dp[i+1][j + item[i].ff], dp[i][j] + item[i].ss);
        
                }
            }
        }
    }
    
    int rt = 0;
    F1(K) smax(rt,dp[N][i]);

    return rt;
}
int RandInt(int l, int r) {
    return rand() % (r - l + 1) + l;
}

double RandDb() {
    return (double)rand() / RAND_MAX;
}
class Evo{
public:
    Evo(const vector<pii>& items) : item(items) {
        
        F(PS) pop.pb(GeraResposta());
    }
    void genicide(){
        pop.clear();
        cout << "GENOCIDIO\n";
        F(PS) {
            if(i%10 == 0)
                pop.pb(crossover(cr7,GeraResposta()));
            else
                pop.pb(GeraResposta());
        }
    }

    

    int best() {
        int bestfit = 0;
        bitset<N> bestasw;

        for (const auto& ind : pop) {
            int fit = testa(ind);
            if (fit > bestfit) {
                bestfit = fit;
                bestasw = ind;
            }
        }
        
        return bestfit;
    }
    bitset<N> bestbm() {
        int bestfit = 0;
        bitset<N> bestasw;

        for (const auto& ind : pop) {
            int fit = testa(ind);
            if (fit > bestfit) {
                bestfit = fit;
                bestasw = ind;
            }
        }
        return bestasw;
    }
    void evolve() {
        vector<pii> fit; 
        for (int i = 0; i < PS; i++) {
            fit.pb({testa(pop[i]), i});
        }

        sort(all(fit));
        reverse(all(fit));

        

        vector<bitset<N>> novo;
        for (int i = 0; i < PS / 2; i++) {
            novo.push_back(pop[fit[i].second]);
        }

        while (novo.size() < PS) {
            int p1 = RandInt(0, PS/10 -1);
            int p2 = RandInt(0, PS/10 -1);
            
            bitset<N>  child = crossover(novo[p1], novo[p2]);
            mutate(child);
            novo.pb(child);
           
        }
        
        pop = novo;
        if(testa(cr7) < testa(best())) cr7 = bestbm();
    }

    vector<pii> item;   
    vector<bitset<N>> pop;  
    bitset<N> cr7 = GeraResposta();

    
    bitset<N> GeraResposta() {
        bitset<N> res;
        for (int i = 0; i < N; i++) {
            res[i] = RandInt(0, 1); 
        }
        return res;
    }


    int testa(const bitset<N>& solution) {
        int res = 0, sum = 0;
        for (int i = 0; i < N; i++) {
            if (solution[i]) {
                sum += item[i].weight;
                res += item[i].value;
            }
        }
        if (sum > K) {
            res -= (sum - K) *10;
        }
        return res;
    }


    bitset <N> crossover(const bitset<N>& p1, const bitset<N>& p2) {
        bitset <N> res;
        int r = RandInt(0, N-1);
        F(N) res[i] = (rand()%2) ? p1[i] : p2[i];
        return res;
    }

    void mutate(bitset<N>& solution) {
        for (int i = 0; i < N; i++) {
            if (RandDb() < MR) {
                solution.flip(i); 
            }
        }
    }
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    srand(time(0));

    item.resize(N + 10);

    F(N) cin >> item[i].weight;
    F(N) cin >> item[i].value;
    
   
    int res = solve_dp();

    int guloso  = 0, gsum = 0;
    vector <pair<float,int>> vg;
    F(N) vg.pb({item[i].value/item[i].weight,i});
    sort(all(vg));
    reverse(all(vg));
    
    F(N){
        if(gsum + item[vg[i].ss].weight > K) break;

        gsum += item[vg[i].ss].weight;
        guloso += item[vg[i].ss].value;
    }

    int ct = 0;
    Evo evo(item);
    double mean = 0;
    queue <double> lasts;
    while(ct <4e2 && evo.best() != res){
        ct++;
        
        if(ct > 50) {
            if(abs(mean-evo.best()) < 100)
                evo.genicide();
            //cout << mean << " " << evo.best() << "\n";
            mean -= lasts.front();
            lasts.pop();
        }
        evo.evolve();

        mean += (float)evo.best()/50;
        lasts.push((float)evo.best()/50);
        MR = 0.002;
        
    }
    cout << "Quantidade de rodadas: " << ct << "\n";
    cout << "DP: " << res << "\n";
    cout << "Evolutivo: " << evo.best() << "\n";
    cout << "Guloso: " << guloso << "\n";
}