#include <vector>

class Parser
{
private:
    std::vector<std::string> m_tokens;
private:
    void ReadTokens();
private:
    void LogTokens();
public:
    Parser();
    double Differentiation();
    double Integration();
    void Cleanup();
};