#include "resources_holder.h"


namespace Core {
    Resource_Holder& Resource_Holder::get()
    {
        static Resource_Holder holder;
        return holder;
    }

    Resource_Holder::Resource_Holder()
        : fonts("fonts", "ttf")
        , textures("txrs", "png")
        
    {

    }
}