#pragma once
#include "Gates/Basic.hpp"

namespace sequential {
    class SRLatch {
        private:
            bool Q;
            bool Q_bar;

        public:
            SRLatch();

            void set(bool S, bool R);
            bool getQ() const;
            bool getQ_bar() const;
    };

    class DLatch {
        private:
            SRLatch sr;
        public:
            void set(bool D, bool Enable);
            bool getQ() const;
    };
}