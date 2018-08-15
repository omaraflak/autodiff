#ifndef BINARY_OPERATION_RESULT
#define BINARY_OPERATION_RESULT

struct BinaryOperationResult {
    double value;
    double left_grad;
    double right_grad;

    BinaryOperationResult(double value, double left_grad, double right_grad){
        this->value = value;
        this->left_grad = left_grad;
        this->right_grad = right_grad;
    }
};

#endif /* end of include guard: BINARY_OPERATION_RESULT */
