#include <fstream>
#include <vector>
#include <string>
#include <cstddef>

class MergeSort
{

  private:
    typedef std::vector<int> buffer_t;
    static int itemsPerPage;
    static int pagesPerBuffer;
    static int numBuffers;
    static int numPages;
    static std::string filename;
    static std::vector<buffer_t> listOfBuffers;

    static void pass0();
    static void passN(int);
    static buffer_t innerSort(buffer_t, buffer_t);

  public:
    MergeSort(int, int, std::string);
    ~MergeSort();
    static void run();
};
