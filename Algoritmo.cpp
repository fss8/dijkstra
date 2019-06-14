#include <iostream>
#define INFINITO 999
using namespace std;

int D[100000],F[100000];

struct RetornoHeap{
    int dist;
    int vertice;
};

struct CaminhoDistante{
    int *Distancia;
    int *Caminho;
};

struct Graph{
    int no;
    int peso;
    Graph * Prox;
};

class GrafoObj{
public:
    Graph ** Graf; int v; CaminhoDistante *Vertice; int tamanho; RetornoHeap *heap;
    GrafoObj(int V){
        Graf = (Graph**)malloc((V)*sizeof(Graph*));
        Vertice = (CaminhoDistante*)malloc((V)*sizeof(CaminhoDistante));
        heap = (RetornoHeap*)malloc((V)*sizeof(RetornoHeap));
        for(int i = 0; i < V; i++){
            Graf[i] = create_raiz(i, 0);
            //cout << Graf[i]->no << " - "<< Graf[i]->peso << "\n";
        }
        v = V;
    }
    int CalculaCaminho(int s, int d){
        Dijkstra(s-1);
        for(int i = 0; i < v; i++) {
            cout << Vertice[s-1].Distancia[i] << "  "; //Meu debuguer
        }
        cout << "\n" << " distancia" << Vertice[s-1].Distancia[d-1];
        return Vertice[s-1].Distancia[d-1];
    }
    void Dijkstra(int s){
        //int e;
        Graph *e;
        for(int i = 0; i < v; i++){
            D[i] = INFINITO;
            F[i] = -1;
            heap[i].vertice = i;
            heap[i].dist = INFINITO;
        }
        D[s] = 0;
        F[s] = s;
        int tam = 0;
        int d,u;
        RetornoHeap a;
        RetornoHeap w;
        //Inserir na heap
        tamanho = v;
        RetornoHeap l; l.dist = 0; l.vertice = s;
        min_heap_insert(l,0);
        while(tamanho > 0){
            a = min_heap_extract();
            d = a.dist;  u = a.vertice;
            e = Graf[u];
            while(e != nullptr){
                if(D[e->no] > d+e->peso){
                    D[e->no] = d+e->peso;
                    F[e->no] = u;
                    w.dist = D[e->no];
                    w.vertice = e->no;
                    min_heap_update(w);
                }
                e = e->Prox;
            }
        }
        Vertice[s].Caminho = (int*)malloc((v)*sizeof(int));
        Vertice[s].Distancia = (int*)malloc((v)*sizeof(int));
        for(int i = 0; i<v; i++){
            Vertice[s].Distancia[i] = D[i];
            Vertice[s].Caminho[i] = F[i];
        }
    }
    void min_heap_insert(RetornoHeap r, int id){
        int pos = id;
        heap[pos].dist = r.dist;
        heap[pos].vertice = r.vertice;
    }
    RetornoHeap min_heap_extract(){
        RetornoHeap z;
        z.vertice = heap[0].vertice;
        z.dist = heap[0].dist;
        TrocaSoldados(0, tamanho-1);
        tamanho--;
        heapfy(0);
        return z;
    }
    void min_heap_update(RetornoHeap t){
        int i;
        for(i = 0; i < tamanho; i++){
            if(heap[i].vertice == t.vertice){
                break;  }
        }
        heap[i].dist = t.dist;
        BubbleUp0(i);
        heapfy(i);
    }
    void heapfy(int i){
        int l = (2*i)+1, r = (2*i)+2, m = i;
        if ((l < tamanho && heap[l].dist < heap[m].dist)) {
            m = l;
        }
        if ((r < tamanho && heap[r].dist < heap[m].dist)) {
            m = r;
        }
        if(m != i) {
            TrocaSoldados(i, m);
            heapfy(m);
        }
    }
    void BubbleUp0(int i){
        int p = (i-1)/2;
        while((i > 0 && heap[i].dist <  heap[p].dist)){
            TrocaSoldados(i, p);
            i = p;
            p = (i-1)/2;
        }
    }
    void TrocaSoldados(int i, int p) {
        int temp1 = heap[i].dist;
        int temp2 = heap[i].vertice;
        heap[i].vertice = heap[p].vertice;
        heap[i].dist = heap[p].dist;
        heap[p].vertice = temp2;
        heap[p].dist = temp1;
    }
    void build_heap(){
        for(int i = (tamanho/2)-1; i >= 0; i--){
            heapfy(i);
        }
    }
    void EncontraProx(int x, int y, int ab){
        if(Graf[x]->Prox == nullptr){
            Graf[x]->Prox = create_raiz(y,ab);
        }else{
            Graph *z = Graf[x]->Prox;
            while(z->Prox != nullptr){
                z = z->Prox;
            }
            z->Prox = create_raiz(y, ab);
        }
    }
    Graph * create_raiz(int val, int ab){
        Graph * aux = (Graph *) malloc(sizeof(Graph));
        aux->no = val;
        aux->peso = ab;
        aux->Prox = nullptr;
        return aux;
    }
};

int main() {
    int T, N, R; int p,q,t; int s, d;
    cin >> T;  cin >> N;
    GrafoObj *GRF; GRF = new GrafoObj(N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++) {
            cin >> p;
            if(p != 0){
                GRF->EncontraProx(i,j,p);
            }
        }
    }
    cin >> R;
    for(int i = 0; i < R; i++){
        cin >> s >> d;
        GRF->CalculaCaminho(s,d);
    }
    return 0;
}
