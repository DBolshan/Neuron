#include <cstddef>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

typedef double (*Func)(double);
class Neuron {
public:
    Neuron(size_t amt, Func func): m_in_a(amt), m_func(func) { }
    Neuron(const Neuron& n): m_in_a(n.m_in_a), m_func(n.m_func) { }

    Neuron& operator=(const Neuron& n) {
        m_in_a = n.m_in_a;
        m_func = n.m_func;
        return *this;
    }

    double get(double* values) const {
        size_t index = 0;
        double summa = 0;
        for (size_t i = 0; i < m_in_a; ++i) {
            summa += values[index] + values[index + 1];
            index += 2;
        }
        return m_func(summa);
    }

private:
    size_t m_in_a;
    Func m_func;
};

double sigma(double tr) {
    return 1 / (1 + exp(-tr));
}

int main() {
    srand(static_cast<unsigned>(time(NULL)));
    int amt = 0;
    fputs("Input: ", stdout);
    scanf("%d", &amt);
    double* value = new double[amt * 2];
    printf("Enter %d pairs: input value and synapse value:\n", amt);
    for (size_t i = 0; i < amt * 2; i += 2) {
        scanf("%lf %lf", value + i, value + i + 1);
    }
    Neuron n(amt, sigma);
    printf("Func is 1 / (1 + exp(-h))\nThere are %d inputs"
        "\nResult is %.9f", amt, n.get(value));
}
