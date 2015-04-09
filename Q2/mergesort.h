#include <fstream>
#include <vector>
#include <string>
#include <cstddef>

class MergeSort
{

  private:
    typedef std::vector<size_t> buffer_t;
    static size_t itemsPerPage;
    static size_t pagesPerBuffer;
    static size_t numBuffers;
    static size_t numPages;
    static std::string filename;
    static std::vector<buffer_t> listOfBuffers;

    static void pass0();
    static void passN(size_t);
    static buffer_t innerSort(buffer_t, buffer_t);

  public:
    MergeSort(size_t, size_t, std::string);
    ~MergeSort();
    static void run();
};
