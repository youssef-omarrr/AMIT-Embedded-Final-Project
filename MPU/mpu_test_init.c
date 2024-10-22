int main() {
    // Create an MPU6050 instance
    MPU6050 mpu;
    
    // Set MPU6050 address
    mpu.address = MPU6050_ADDR;
    
    // Set default gyro and accelerometer sensitivity configurations
    MPU6050_setGyroConfig(&mpu, 0);  // Gyro config 0: +-250 deg/s
    MPU6050_setAccConfig(&mpu, 0);   // Accel config 0: +-2g
    
    // Initialize offsets to 0 (could be calibrated later)
    mpu.gyroXoffset = 0;
    mpu.gyroYoffset = 0;
    mpu.gyroZoffset = 0;
    mpu.accXoffset = 0;
    mpu.accYoffset = 0;
    mpu.accZoffset = 0;
    
    // Set filter coefficient for complementary filter
    mpu.filterGyroCoef = DEFAULT_GYRO_COEFF; // 0.98 by default
    
    // Set upside down mounting flag (false by default)
    mpu.upsideDownMounting = false;
    
    // Example: Fetch and update data from MPU6050
    while (1) {
        MPU6050_fetchData(&mpu);
        MPU6050_update(&mpu);
        
        // You can now access data, for example:
        float angleX = MPU6050_getAngleX(&mpu);
        float angleY = MPU6050_getAngleY(&mpu);
        
        // Do something with the angles...
    }

    return 0;
}
