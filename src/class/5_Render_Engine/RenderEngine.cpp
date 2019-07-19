#include "RenderEngine.hpp"

RenderEngine::RenderEngine(std::string *libDir, int width, int height, int activeLib)
{

    this->libDirectories = new std::string[3];

    for (int i = 0; i < 3; i++)
        this->libDirectories[i] = libDir[i];

    this->width = width;
    this->height = height;
    this->activeLibNum = -1;
    setGraphicLib(activeLib);
}

RenderEngine::RenderEngine(const RenderEngine &obj)
{
    *this = obj;
}

RenderEngine::~RenderEngine()
{
    delete this->dlsym_error;
	delete this->activeLib;
    delete [] libDirectories;
}


RenderEngine &RenderEngine::operator=(RenderEngine const &other)
{
    (void)other;
    return *this;
}


IGraphicsLib *RenderEngine::getGraphicLib() const
{
    return this->activeLib;
}

void RenderEngine::setGraphicLib(int libNumber)
{
    if (libNumber > 2)
        throw RenderEngineExceptions::LibraryNotFoundException();
    
    if (libNumber != this->activeLibNum)
    {
        //Load The Library
        this->graphicLib = dlopen(this->libDirectories[libNumber].c_str(), RTLD_LAZY);
        
        if (!graphicLib) {
            // std::cerr << "Cannot load library: " << dlerror() << '\n';
            //Throw Custom Exception, with error string 
            throw RenderEngineExceptions::LibraryNotFoundException();
        }

        //Reset errors
        dlerror();

        //Load Symbols
        this->createLib = (createLib_t *) (dlsym(this->graphicLib, "createLib"));
        this->dlsym_error = dlerror();

        if (dlsym_error) {
            //std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
            //Throw Custom Exception, with error string 
            return ;
        }

        this->destroyLib = (destroyLib_t *) (dlsym(this->graphicLib, "destroyLib"));
        this->dlsym_error = dlerror();

        if (dlsym_error) {
            //std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
            //Throw Custom Exception, with error string 
            return ;
        }

        this->activeLib = this->createLib();
        this->activeLib->init(this->width, this->height, "Nibbler");
        this->activeLibNum = libNumber;
    }
}

void RenderEngine::resetGraphicLib()
{
    this->destroyLib(this->activeLib);
}

void RenderEngine::changeGraphicLib(int libNumber)
{
    if (libNumber != this->activeLibNum)
    {
        resetGraphicLib();
        setGraphicLib(libNumber);
    }
}

int RenderEngine::getWidth() const
{
    return this->width;
}

int RenderEngine::getHeight() const
{
    return this->height;
}

int RenderEngine::getActiveLibNum() const
{
    return this->activeLibNum;
}

void RenderEngine::setLibDirectories(std::string libDir[])
{
    for (int i = 0; i < 3; i++)
        this->libDirectories[i] = libDir[i];
}

std::string *RenderEngine::getLibDirectories() const
{
    return this->libDirectories;
}