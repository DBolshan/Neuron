#include <cstddef>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

typedef double (*Func)(double);
class Neuron {
public:
    double *data;
    double *koeff;
    Neuron(size_t amt, Func func, double* mas): m_in_a(amt), m_func(func) {
        this->data = new double[amt];
        this->koeff = new double[amt];
        for (unsigned int i = 0; i < amt; i++){
            this->data[i] = mas[i + (i % 2)];
        }
        for (unsigned int i = 0; i < amt; i++){
            this->koeff[i] = mas[i + (i % 2) + 1];
        }
    }
    Neuron(const Neuron& n): m_in_a(n.m_in_a), m_func(n.m_func) { }

    Neuron& operator=(const Neuron& n) {
        m_in_a = n.m_in_a;
        m_func = n.m_func;
        return *this;
    }

    double get(double* values, double* kff) const {
        double summa = 0;
        for (size_t i = 0; i < m_in_a; ++i) {
            summa += values[i] * kff[i];
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
    Neuron n(amt, sigma, value);
    printf("Func is 1 / (1 + exp(-h))\nThere are %d inputs"
        "\nResult is %.9f", amt, n.get(n.data, n.koeff));
}
