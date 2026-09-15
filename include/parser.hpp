#include <vector>
#include "differentiator.hpp"
#include "integrator.hpp"

class Parser
{
private:
    std::vector<std::string> m_tokens;
    Integrator m_integrator;
    Differentiator m_differentiator;
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