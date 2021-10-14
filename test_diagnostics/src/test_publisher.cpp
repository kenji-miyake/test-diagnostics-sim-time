
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <diagnostic_msgs/msg/diagnostic_status.hpp>
#include <diagnostic_msgs/msg/diagnostic_array.hpp>

class TestPublisher : public rclcpp::Node
{
public:
  TestPublisher()
      : Node("test_publisher")
  {
    pub_ = this->create_publisher<diagnostic_msgs::msg::DiagnosticArray>("/diagnostics", 1);

    // Timer
    const auto update_period_ns = rclcpp::Rate(1).period();
    timer_ = rclcpp::create_timer(
        this, get_clock(), update_period_ns, std::bind(&TestPublisher::onTimer, this));
  }

private:
  void onTimer()
  {
    diagnostic_msgs::msg::DiagnosticArray msg;
    msg.header.stamp = get_clock()->now();
    RCLCPP_INFO(get_logger(), "%s", rosidl_generator_traits::to_yaml(msg).c_str());

    diagnostic_msgs::msg::DiagnosticStatus status;
    status.name = "test_publisher";
    status.level = diagnostic_msgs::msg::DiagnosticStatus::WARN;
    msg.status.push_back(status);

    pub_->publish(msg);
  }

  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr pub_{};
  rclcpp::TimerBase::SharedPtr timer_{};
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TestPublisher>();
  auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
  executor->add_node(node);
  executor->spin();
  rclcpp::shutdown();

  return 0;
}
