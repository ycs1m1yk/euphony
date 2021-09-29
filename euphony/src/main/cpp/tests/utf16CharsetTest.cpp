    #include <gtest/gtest.h>
    #include <Definitions.h>
    #include <UTF16Charset.h>
    #include <tuple>

    using namespace Euphony;

    typedef std::tuple<std::string, std::string> TestParamType;

    class UTF16CharsetTestFixture : public ::testing::TestWithParam<TestParamType> {

    public:
        void openCharset() {
            EXPECT_EQ(charset, nullptr);
            charset = new UTF16Charset();
            ASSERT_NE(charset, nullptr);
        }

        Charset* charset = nullptr;
    };


    TEST_P(UTF16CharsetTestFixture, EncodingTest)
    {
    openCharset();

    std::string source;
    std::string expectedResult;

    std::tie(source, expectedResult) = GetParam();
    HexVector actualResult = charset->encode(source);
    EXPECT_EQ(actualResult.toString(), expectedResult);
    }


    TEST_P(UTF16CharsetTestFixture, DecodingTest)
    {
    openCharset();

    std::string source;
    std::string expectedResult;

    std::tie(expectedResult, source) = GetParam();
    HexVector hv = HexVector(source);

    std::string actualResult = charset->decode(hv);
    EXPECT_EQ(actualResult, expectedResult);
    }

    INSTANTIATE_TEST_CASE_P(
            ChrasetDecodingTestSuite,
            UTF16CharsetTestFixture,
            ::testing::Values(
            TestParamType("가", "ac00")
    ));