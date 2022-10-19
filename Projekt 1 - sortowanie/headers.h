void randtab(unsigned int* tab,unsigned int start, unsigned int size);
void readtab(const unsigned int* tab, unsigned int from,unsigned int to);
void readtabtofile(const unsigned int* tab,unsigned int from,unsigned int to);

void buildHeap(unsigned int* tab, unsigned int size); // F-cja budująca kopiec
void stripHeap(unsigned int* tab, unsigned int size); // F-cja rozbierająca kopiec

void cleanTab(unsigned int* tab, unsigned int size);
void cleanTab(float* tab, unsigned int size);

void merge(unsigned int* tab,unsigned int* pom, const unsigned int ip, const unsigned int is,const unsigned int ik);
void mergeSort(unsigned int* tab,unsigned int* pom,const unsigned int ip,const unsigned int ik);

void quicksort(unsigned int* tab,const unsigned int left,const unsigned int right);

void shellSort(unsigned int *tab1,const unsigned int size);
// Sprawdza poprawność sortowania tablicy, 
// arg type:  'm' - tab. posortowana malejąco
//            'r' - tab. posortowana rosnąco
// Zwraca 1, gdy poprawnie, 0 gdy niepoprawnie posortowana
bool checkSort(const unsigned int* tab1,const unsigned int size, const char type);

// odwraca kolejnosc el. tablicy, np. z posortowanych rosnąco, a posortowane malejąco
void reverseTab(unsigned int* tab1, const unsigned int size);

// funkcja tworząca tablice o losowych elementach, częściowo posortowaną
// part - część tablicy posortowanej od początku w promilach
void make(unsigned int *tab, unsigned int size, unsigned int part);
