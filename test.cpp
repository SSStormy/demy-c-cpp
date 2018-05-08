#include <gtest/gtest.h>

#define DEMCPPY_IMPLEMENTATION 1
#include <demcppy.h>

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

TEST(Timelines, CreationReturnsExistingTimeline)
{
    Timeline tl;
    auto tr1 = "camera.x";

    Track track1 = tl.GetTrack(tr1);
    Track track2 = tl.GetTrack(tr1);

    EXPECT_EQ(track1.GetCPtr(), track2.GetCPtr());
}

TEST(Timelines, SerializeDeserialize)
{
    auto save_file = "test-save.json";
    auto track1_name = "camera.x";
    auto track2_name = "camera.y";

    {
        Timeline tl;
        Track track1 = tl.GetTrack(track1_name);
        Track track2 = tl.GetTrack(track2_name);

        track1.AddNode(10, 1.0, InterpType::Linear);
        track1.AddNode(20, 2.0, InterpType::Linear);

        track2.AddNode(20, 2.0, InterpType::None);
        track2.AddNode(40, 4.0, InterpType::None);

        tl.Save(save_file);
    }

    {
        Timeline tl = Timeline::Load(save_file);

        Track track1 = tl.GetTrack(track1_name);
        Track track2 = tl.GetTrack(track2_name);

        {
            // TODO
            Node node1;
        }

    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
