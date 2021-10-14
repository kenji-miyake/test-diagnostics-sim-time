
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <diagnostic_msgs/msg/diagnostic_status.hpp>
#include <diagnostic_updater/diagnostic_updater.hpp>

class TestUpdaterNode : public rclcpp::Node
{
public:
  TestUpdaterNode()
      : Node("test_updater")
  {
    updater_.setHardwareID("test_updater");
    updater_.add("test_updater", this, &TestUpdaterNode::onUpdate);
  }

private:
  void onUpdate(diagnostic_updater::DiagnosticStatusWrapper &stat)
  {
    using diagnostic_msgs::msg::DiagnosticStatus;
    int8_t level = DiagnosticStatus::ERROR;
    std::string msg = "test_updater";

    stat.summary(level, msg);
  }

  diagnostic_updater::Updater updater_{this};
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TestUpdaterNode>();
  auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
  executor->add_node(node);
  executor->spin();
  rclcpp::shutdown();

  return 0;
}
