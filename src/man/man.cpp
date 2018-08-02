#include "man.h"

namespace man {

Man::Man() {
    std::cout << "Man constructed" << std::endl;
}


Man::~Man()
{
    std::cout << "Man is being killed" << std::endl;
}

} // namespace man
