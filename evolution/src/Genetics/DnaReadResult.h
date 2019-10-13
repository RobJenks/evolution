#include <memory>
#include <string>
#include "../Util/Result.h"
class Entity;

typedef Result<std::unique_ptr<Entity>, std::string> DnaReadResult;
