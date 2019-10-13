#include <memory>
#include <string>
#include "../Util/Result.h"
class Dna;

typedef Result<std::unique_ptr<Dna>, std::string> DnaWriteResult;
