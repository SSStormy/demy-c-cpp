#include <gtest/gtest.h>

#define DEMCPPY_IMPLEMENTATION 1
#include <demcppy.h>

// timeline creation, deletion
// timeline creation returns existing timeline

using namespace Demy;
TEST(Timelines, CreateDelete)
{
    Timeline tl;
    EXPECT_TRUE(tl.GetCPtr() != 0);

    Track track1 = tl.GetTrack("camera.x");
    Track track2 = tl.GetTrack("camera.y");

    EXPECT_NE(track1.GetCPtr(), track2.GetCPtr());

    bool del_result = tl.DeleteTrack("i_dont_exist");
    EXPECT_FALSE(del_result);

    del_result = tl.DeleteTrack("camera.x");
    EXPECT_TRUE(del_result);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
