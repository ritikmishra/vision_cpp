echo "Compiling . . ."

file="Vision"
g++ -o "$file" "$file.cpp" Utils.h Utils.cpp -I/usr/local/include/networktables -I/usr/local/include/opencv -I/usr/local/include -L/usr/local/lib -lntcore -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core -std=gnu++11
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
