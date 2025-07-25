__kernel void add_one(__global float* data) {
    int i = get_global_id(0);
    data[i] += 1.0f;
}

