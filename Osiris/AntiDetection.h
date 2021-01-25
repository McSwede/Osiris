#ifdef _WIN32
#include <memory>

class AntiDetection
{
public:
	AntiDetection();
};

inline std::unique_ptr<AntiDetection> antiDetection;
#endif