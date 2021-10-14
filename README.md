# test-diagnostics-sim-time

## Usage

```sh
git clone https://github.com/kenji-miyake/test-diagnostics-sim-time.git
cd test-diagnostics-sim-time
source /opt/ros/galactic/setup.bash
colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release
source install/setup.bash

# Terminal 1
ros2 launch test_diagnostics test.launch.xml use_sim_time:=true

# Terminal 2
ros2 topic echo /clock

# Terminal 3
ros2 topic echo /diagnostics

# Terminal 4
ros2 topic echo /diagnostics_agg --no-arr
```

To use the fixed version of `diagnostics`,

```sh
cd test-diagnostics-sim-time
git clone https://github.com/tier4/diagnostics.git -b fix-sim-time-bug
```
