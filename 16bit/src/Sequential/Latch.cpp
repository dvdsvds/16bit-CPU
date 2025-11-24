#include "Sequential/Latch.hpp"

namespace sequential {
    SRLatch::SRLatch() : Q(false), Q_bar(true) {}

    void SRLatch::set(bool S, bool R) {
        bool prev_Q, prev_Q_bar;
        do {
            prev_Q = Q;
            prev_Q_bar = Q_bar;

            Q = gate::NOR(R, Q_bar);
            Q_bar = gate::NOR(S, Q);
        } while(Q != prev_Q || Q_bar != prev_Q_bar);
    }

    bool SRLatch::getQ() const {
        return Q;
    }

    bool SRLatch::getQ_bar() const {
        return Q_bar;
    }

    void DLatch::set(bool D, bool Enable) {
        bool S = gate::AND(D, Enable);
        bool R = gate::AND(gate::NOT(D), Enable);

        sr.set(S, R);
    }

    bool DLatch::getQ() const {
        return sr.getQ();
    }
}