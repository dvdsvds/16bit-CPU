#include "Sequential/RegisterFile.hpp"

namespace sequential {
    void RegisterFile::write(Bit3 addr, const Bit16& data, bool enable, bool clock) {
        for(size_t i = 0; i < BIT8; ++i) {
            Bit3 cur_num = utils::IntToBit3(i);

            bool s1 = gate::XNOR(cur_num[0], addr[0]);
            bool s2 = gate::XNOR(cur_num[1], addr[1]);
            bool s3 = gate::XNOR(cur_num[2], addr[2]);

            bool result = gate::AND(gate::AND(s1, s2), s3);
            bool load_signal = gate::AND(result, enable);

            registerArray[i].set(data, load_signal, clock);
        }
    }

    RegisterFile::RegisterFileResult RegisterFile::read(Bit3 addr1, Bit3 addr2) const {
        std::array<Bit16, BIT8> arr;
        RegisterFileResult result;
        for(size_t i = 0; i < BIT8; ++i) {
            arr[i] = registerArray[i].read();

        }
        result.data1 = selector::MUX8(arr, addr1); 
        result.data2 = selector::MUX8(arr, addr2);

        return result;
    }
}