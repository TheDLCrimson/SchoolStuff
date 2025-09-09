import numpy as np
import matplotlib.pyplot as plt
import os

import neural_network

def max_score():
    return 2

def timeout():
    return 60

def load_labels(filename):
    f = open(filename, 'r', encoding = "UTF8").readlines()
    labels = []
    for s in f:
        curlabel = int(s[:s.find('\n')])
        labels.append(curlabel)
    return labels

def check_metrics(expec, actua, tol):
    correct_count = 0
    total_count = len(expec)
    for i in range(total_count):
        e_metric = expec[i]
        a_metric = actua[i]
        error = abs(e_metric-a_metric)/(e_metric+0.0000000000000001)
        if error <= tol:
            correct_count += 1
    score = float(correct_count)/float(total_count)
    return score

def check_labels(expec, actua):
    match = np.sum((expec == actua).astype(float))
    total_count = len(expec)
    score = float(match) / float(total_count)
    return score

def run_and_testNN(test_params, expected, max_points, test_labels = True):
    X_train, y_train, X_val, y_val = neural_network.load_data_small()
    num_epoch = test_params["num_epoch"]
    num_hidden = test_params["num_hidden"]
    init_rand = test_params["init_rand"]
    learning_rate = test_params["learning_rate"]
    result = neural_network.train_and_test(X_train, y_train, X_val, y_val,
                num_epoch, num_hidden, init_rand, learning_rate)

    actual_loss_per_epoch_train = result[0]
    actual_loss_per_epoch_val = result[1]
    actual_err_train = result[2]
    actual_err_val = result[3]
    actual_y_hat_train = result[4]
    actual_y_hat_val = result[5]

    expected_loss_per_epoch_train = expected["expected_loss_per_epoch_train"]
    expected_loss_per_epoch_val = expected["expected_loss_per_epoch_val"]
    expected_err_train = expected["expected_err_train"]
    expected_err_val = expected["expected_err_val"]

    if (test_labels):
        expected_train_labels_list = load_labels("Reference_Outputs/" + expected["expected_y_hat_train"])
        expected_y_hat_train = np.asarray(expected_train_labels_list)
        expected_val_labels_list = load_labels("Reference_Outputs/" + expected["expected_y_hat_val"])
        expected_y_hat_val = np.asarray(expected_val_labels_list)
    
    score = 0
    num_checks = 0
    tol = 0.01
    if init_rand:
        tol = 0.15

    msg_list = ['']
    if init_rand:
        exp_acc = 0.95
    else:
        exp_acc = 1.0

    #checking training metrics
    assert (len(actual_loss_per_epoch_train) == len(expected_loss_per_epoch_train)), 'Incorrect length found for Train Loss. Expected {}, found {}.'.format(len(expected_loss_per_epoch_train), len(actual_loss_per_epoch_train))
    cur_score = check_metrics(expected_loss_per_epoch_train, actual_loss_per_epoch_train, tol)
    if init_rand and cur_score >= 0.95:
        cur_score = 1.0
    score += cur_score
    if abs(cur_score - 1) > 0.000001:
        msg_list.append('Incorrect cross entropy loss found in Train Loss. Expected matching accuracy {}, found actual accuracy {}.'.format(exp_acc, cur_score))
    num_checks += 1



    # checking testing metrics
    assert (len(actual_loss_per_epoch_val) == len(expected_loss_per_epoch_val)), 'Incorrect length found for Validation Loss. Expected {}, found {}.'.format(len(expected_loss_per_epoch_val), len(actual_loss_per_epoch_val))
    cur_score = check_metrics(expected_loss_per_epoch_val, actual_loss_per_epoch_val, tol)
    if init_rand and cur_score >= 0.95:
        cur_score = 1.0
    score += cur_score
    if abs(cur_score - 1) > 0.0000000000000001:
        msg_list.append('Incorrect cross entropy loss found in Validation Loss. Expected matching accuracy {}, found actual accuracy {}.'.format(exp_acc, cur_score))
    num_checks += 1


    # checking labels
    if (test_labels):
        assert (len(expected_y_hat_train) == len(actual_y_hat_train)), 'Incorrect length found for Train Labels. Expected {}, found {}.'.format(len(expected_y_hat_train), len(actual_y_hat_train))
        match = check_labels(expected_y_hat_train, actual_y_hat_train)
        cur_score = 0
        if match >= 0.65:
            cur_score = (match - 0.65) / 0.35
        if abs(cur_score - 1) > 0.000001:
            msg_list.append('Incorrect prediction found for Train Labels. Expected matching accuracy {}, found actual accuracy {}.'.format(exp_acc, cur_score))
        num_checks += 1
        score += cur_score

        # assert abs(train_labels_diff) < 0.01, 'Incorrect prediction found for Train Labels. {} labels are predicted incorrectly'.format(train_labels_diff)
        assert (len(expected_y_hat_val) == len(actual_y_hat_val)), 'Incorrect length found for Validation Labels. Expected {}, found {}.'.format(len(expected_y_hat_val), len(actual_y_hat_val))
        match_test = check_labels(expected_y_hat_train, actual_y_hat_train)
        cur_score = 0
        if match_test >= 0.65:
            cur_score = (match_test - 0.65) / 0.35
        num_checks += 1
        if abs(cur_score - 1) > 0.000001:
            msg_list.append('Incorrect prediction found for Validation Labels. Expected matching accuracy {}, found actual accuracy {}.'.format(exp_acc, cur_score))
        score += cur_score

    test_score = score / num_checks * max_points
        # assert abs(val_labels_diff) < 0.01, 'Incorrect prediction found for Validation Labels. {} labels are predicted incorrectly'.format(val_labels_diff)

    # test_score = score
    if len(msg_list) == 1:
        test_output = 'PASS\n'
    else:
        test_output = '\n'.join(msg_list)

    return int(test_score), test_output


