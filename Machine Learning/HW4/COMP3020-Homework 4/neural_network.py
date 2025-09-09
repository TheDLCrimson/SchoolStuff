import numpy as np
np.random.seed(0)

def load_data_small():
    """ Load small training and validation dataset

        Returns a tuple of length 4 with the following objects:
        X_train: An N_train-x-M ndarray containing the training data (N_train examples, M features each)
        y_train: An N_train-x-1 ndarray contraining the labels
        X_val: An N_val-x-M ndarray containing the training data (N_val examples, M features each)
        y_val: An N_val-x-1 ndarray contraining the labels
    """
    train_all = np.loadtxt('data/smallTrain.csv', dtype=int, delimiter=',')
    valid_all = np.loadtxt('data/smallValidation.csv', dtype=int, delimiter=',')

    X_train = train_all[:, 1:]
    y_train = train_all[:, 0]
    X_val = valid_all[:, 1:]
    y_val = valid_all[:, 0]

    return (X_train, y_train, X_val, y_val)


def load_data_medium():
    """ Load medium training and validation dataset

        Returns a tuple of length 4 with the following objects:
        X_train: An N_train-x-M ndarray containing the training data (N_train examples, M features each)
        y_train: An N_train-x-1 ndarray contraining the labels
        X_val: An N_val-x-M ndarray containing the training data (N_val examples, M features each)
        y_val: An N_val-x-1 ndarray contraining the labels
    """
    train_all = np.loadtxt('data/mediumTrain.csv', dtype=int, delimiter=',')
    valid_all = np.loadtxt('data/mediumValidation.csv', dtype=int, delimiter=',')

    X_train = train_all[:, 1:]
    y_train = train_all[:, 0]
    X_val = valid_all[:, 1:]
    y_val = valid_all[:, 0]

    return (X_train, y_train, X_val, y_val)


def load_data_large():
    """ Load large training and validation dataset

        Returns a tuple of length 4 with the following objects:
        X_train: An N_train-x-M ndarray containing the training data (N_train examples, M features each)
        y_train: An N_train-x-1 ndarray contraining the labels
        X_val: An N_val-x-M ndarray containing the training data (N_val examples, M features each)
        y_val: An N_val-x-1 ndarray contraining the labels
    """
    train_all = np.loadtxt('data/largeTrain.csv', dtype=int, delimiter=',')
    valid_all = np.loadtxt('data/largeValidation.csv', dtype=int, delimiter=',')

    X_train = train_all[:, 1:]
    y_train = train_all[:, 0]
    X_val = valid_all[:, 1:]
    y_val = valid_all[:, 0]

    return (X_train, y_train, X_val, y_val)


### FEEL FREE TO WRITE ANY HELPER FUNCTIONS HERE

def sigmoid(x):
    """Compute the sigmoid activation function."""
    return 1 / (1 + np.exp(-x))

def softmax(x):
    """Compute the softmax activation function."""
    exp_x = np.exp(x - np.max(x, axis=1, keepdims=True)) 
    return exp_x / np.sum(exp_x, axis=1, keepdims=True)

def cross_entropy_loss(y, y_hat):
    """Compute cross-entropy loss."""
    m = y.shape[0]
    log_likelihood = -np.log(y_hat[range(m), y])
    loss = np.sum(log_likelihood) / m
    return loss

def accuracy(y, y_hat):
    """Compute accuracy."""
    pred = np.argmax(y_hat, axis=1)
    accuracy = np.mean(pred == y)
    return 1 - accuracy, pred

def initialize_weights(input_size, num_hidden, output_size, init_rand):
    """Initialize weights and biases for the neural network."""
    if init_rand:
        W1 = np.random.uniform(-0.1, 0.1, (input_size, num_hidden))
        b1 = np.zeros((1, num_hidden))
        W2 = np.random.uniform(-0.1, 0.1, (num_hidden, output_size))
        b2 = np.zeros((1, output_size))
    else:
        W1 = np.zeros((input_size, num_hidden))
        b1 = np.zeros((1, num_hidden))
        W2 = np.zeros((num_hidden, output_size))
        b2 = np.zeros((1, output_size))

    return W1, b1, W2, b2

def forward_pass(x, W1, b1, W2, b2):
    """Perform the forward pass."""
    # Hidden layer
    z1 = np.dot(x, W1) + b1  
    a1 = sigmoid(z1)  
    # Output layer
    z2 = np.dot(a1, W2) + b2  
    a2 = softmax(z2)  
    return z1, a1, z2, a2

def backward_pass(x, y, a1, a2, W2):
    """Perform the backward pass to compute gradients."""
    # Output layer
    delta2 = a2 
    delta2[0, y] -= 1
    dW2 = np.dot(a1.T, delta2)
    db2 = delta2
    # Hidden layer
    delta1 = np.dot(delta2, W2.T) * a1 * (1 - a1)
    dW1 = np.dot(x.T, delta1) 
    db1 = delta1

    return dW1, db1, dW2, db2

def update(a, da, learning_rate):
    """Update the weights and biases."""
    return a - learning_rate * da

def validate(y, a2):
    """Compute the loss and accuracy on the validation set."""
    loss = cross_entropy_loss(y, a2)
    err, y_hat = accuracy(y, a2)
    
    return loss, err, y_hat
    
def train_and_test(X_train, y_train, X_val, y_val, num_epoch, num_hidden, init_rand, learning_rate):
    """ Main function to train and validate your neural network implementation.

        X_train: Training input in N_train-x-M numpy nd array. Each value is binary, in {0,1}.
        y_train: Training labels in N_train-x-1 numpy nd array. Each value is in {0,1,...,K-1},
            where K is the number of classes.
        X_val: Test input in N_val-x-M numpy nd array. Each value is binary, in {0,1}.
        y_val: Test labels in N_val-x-1 numpy nd array. Each value is in {0,1,...,K-1},
            where K is the number of classes.
        num_epoch: Positive integer representing the number of epochs to train (i.e. number of
            loops through the training data).
        num_hidden: Positive integer representing the number of hidden units.
        init_rand: Boolean value that is True if we want to initialize all weights to
            random values in Uniform[-0.1, 0.1], or False if weights should be initialized
            to zero. Bias should be initialized to 0 in both cases.
        learning_rate: Float value specifying the learning rate for SGD.

        RETURNS: a tuple of the following six objects, in order:
        loss_per_epoch_train: A list of float values containing the mean cross entropy on training data after each SGD epoch
        loss_per_epoch_val: A list of float values containing the mean cross entropy on validation data after each SGD epoch
        err_train: Float value containing the training error after final SGD epoch (equivalent to 1.0 - accuracy rate)
        err_val: Float value containing the validation error after final SGD epoch (equivalent to 1.0 - accuracy rate)
        y_hat_train: A list of integers representing the predicted labels for training data
        y_hat_val: A list of integers representing the predicted labels for validation data
    """
    ### YOUR CODE HERE
    
    loss_per_epoch_train = []
    loss_per_epoch_val = []

    input_size = X_train.shape[1]
    output_size = len(np.unique(y_train))  

    W1, b1, W2, b2 = initialize_weights(input_size, num_hidden, output_size, init_rand)

    for epoch in range(num_epoch):
        for i in range(X_train.shape[0]):
            x = X_train[i:i+1]
            y = y_train[i:i+1]
            
            z1, a1, z2, a2 = forward_pass(x, W1, b1, W2, b2)
           
            dW1, db1, dW2, db2 = backward_pass(x, y, a1, a2, W2)
           
            W1 = update(W1, dW1, learning_rate)
            b1 = update(b1, db1, learning_rate)
            W2 = update(W2, dW2, learning_rate)
            b2 = update(b2, db2, learning_rate)

        z1_train, a1_train, z2_train, a2_train = forward_pass(X_train, W1, b1, W2, b2)
        loss_train, err_train, y_hat_train = validate(y_train, a2_train)
        loss_per_epoch_train.append(loss_train)

        z1_val, a1_val, z2_val, a2_val = forward_pass(X_val, W1, b1, W2, b2)
        loss_val, err_val, y_hat_val = validate(y_val, a2_val)
        loss_per_epoch_val.append(loss_val)

    return (loss_per_epoch_train, loss_per_epoch_val, err_train, err_val, y_hat_train, y_hat_val)



