#include <gtest/gtest.h>
#include <safe_cast.h>

TEST(BIT_CAST, pointer){
    uint64_t x = 100;
    uint8_t* p = reinterpret_cast<uint8_t*>(&x);

    auto y = bits::bit_cast<uint64_t>(p);

    EXPECT_EQ(x, y);
}

TEST(BIT_CAST, integral_smaller){
    uint64_t x = ~0;
    uint8_t y8 = ~0;
    uint16_t y16 = ~0;
    uint32_t y32 = ~0;
    uint64_t y64 = ~0;

    auto z8 = bits::bit_cast<uint8_t>(x);

    EXPECT_EQ(z8, y8);

    auto z16 = bits::bit_cast<uint16_t>(x);

    EXPECT_EQ(z16, y16);


    auto z32 = bits::bit_cast<uint32_t>(x);

    EXPECT_EQ(z32, y32);

    auto z64 = bits::bit_cast<uint64_t>(x);

    EXPECT_EQ(z64, y64);
}

TEST(BIT_CAST, integral_larger){
    uint8_t x = ~0;

    auto z8 = bits::bit_cast<uint8_t>(x);

    EXPECT_EQ(z8, x);

    auto z16 = bits::bit_cast<uint16_t>(x);

    EXPECT_EQ(z16, x);


    auto z32 = bits::bit_cast<uint32_t>(x);

    EXPECT_EQ(z32, x);

    auto z64 = bits::bit_cast<uint64_t>(x);

    EXPECT_EQ(z64, x);
}

TEST(BIT_CAST, signed_unsigned){
    int64_t sx = -2;
    uint32_t ux = 0xdeadbeef;

    uint16_t uy = 0xfffe;

    auto u16 = bits::bit_cast<uint16_t>(sx);

    EXPECT_EQ(uy, u16);

    auto s64 = bits::bit_cast<int64_t>(ux);

    EXPECT_EQ(s64, ux);

    int32_t sxx = -14;
    auto u64 = bits::bit_cast<uint64_t>(sxx);
    auto expected64 = static_cast<uint64_t>(static_cast<uint32_t>(sxx));

    EXPECT_EQ(u64, expected64);

}

TEST(BIT_CAST, fp){
    float fx = 5.235;
    double dx = 6.789;
    auto ux = static_cast<uint64_t>(*reinterpret_cast<uint32_t*>(&fx));
    auto ux2 = *reinterpret_cast<uint64_t*>(&dx);
    auto bx = bits::bit_cast<uint64_t>(fx);
    auto bx2 = bits::bit_cast<uint64_t>(dx);
    EXPECT_EQ(bx, ux);
    EXPECT_EQ(bx2, ux2);

    uint32_t sy = 0xdeadbeef;
    auto sy64 =  static_cast<uint64_t>(sy);
    auto dy = *reinterpret_cast<double*>(&sy64);
    auto by = bits::bit_cast<double>(sy);

    EXPECT_EQ(dy, by);
}

TEST(BIT_CAST, bool){
    int64_t b1 = 0xf6;
    bool b2 = *reinterpret_cast<bool*>(&b1);
    bool b3 = bits::bit_cast<bool>(b1);
#ifdef __clang__
    EXPECT_TRUE(b2 == b3);
#else 
    EXPECT_TRUE(b2);
    EXPECT_TRUE(b3);
#endif    

    uint32_t b4 = 0xdeadbeef;
    b2 = *reinterpret_cast<bool*>(&b4);
    b3 = bits::bit_cast<bool>(b4);
    EXPECT_TRUE(b2);
    EXPECT_TRUE(b3); 
    	

    bool b5 = 0xbeef;
    auto utmp = static_cast<uint64_t>(b5);
    auto u1 = *reinterpret_cast<uint64_t*>(&utmp);
    auto u2 = bits::bit_cast<uint64_t>(b5);
    EXPECT_EQ(u1, u2);

    auto b6 = bits::bit_cast<bool>(b5);
    EXPECT_EQ(b5, b6);

    auto f1 = 5.6556f;
    b2 = *reinterpret_cast<bool*>(&f1);
    b3 = bits::bit_cast<bool>(f1);
    EXPECT_EQ(b5, b6);

    auto d1 = 5.6556;
    b2 = *reinterpret_cast<bool*>(&d1);
    b3 = bits::bit_cast<bool>(d1);
    EXPECT_EQ(b5, b6);

    auto u3 = static_cast<uint32_t>(b5);
    auto f2 = *reinterpret_cast<float*>(&u3);
    auto f3 = bits::bit_cast<float>(b5);
    EXPECT_EQ(f2, f3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
