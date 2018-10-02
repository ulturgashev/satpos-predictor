#include <gtest/gtest.h>

#include "Predictor.h"

constexpr auto filename = "../../../tests/prediction-qt/samples/MCCJ_170102.agl";

TEST(PredictiorTest, ReadAglFileTest)
{
	std::map<int, Core::Almanach> almanachs = Core::Predictor::readAglFile(filename);
	ASSERT_EQ(almanachs.size(), 24);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
