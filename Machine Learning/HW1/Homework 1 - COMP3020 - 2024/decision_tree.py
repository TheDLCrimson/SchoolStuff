import numpy as np
from utils import split_generator, Node, Split
import argparse
from collections import Counter


class DecisionTree:
    """
    A decision tree classifier for use with real-valued attributes.
    """

    def __init__(self, max_depth=np.inf, mode="ig"):
        """
        Decision tree constructor.

        :param max_depth: limit on the tree depth.
                          A depth 0 tree will have no splits.
        """
        self.max_depth = max_depth
        self._root = None  # Initialize the root node
        self.mode = mode

    def fit(self, X, y):
        """
        Construct the decision tree using the provided data and labels.

        :param X: Numpy array with shape (num_samples, num_features)
        :param y: Numpy integer array with length num_samples
        """
        self.classes = set(y)  # Store the unique classes in the dataset
        self._root = self._fit_tree(X, y, depth=0)

    def predict(self, X):
        """
        Predict labels for a data set by finding the appropriate leaf node for
        each input and using the majority label as the prediction.

        :param X:  Numpy array with shape (num_samples, num_features)
        :return: A length num_samples numpy array containing predicted labels.

        Hint: to implement the prediction function, here are the steps:
             1. Iterate through each input sample.
             2. Traverse the tree until it reaches a leaf.
                 - Uses the `dim` and the `pos` variable from the split to 
                 check which branch to select:
                     - If the value in feature `dim` of `X` is smaller than
                     or equal to `pos`, traverse to the left node.
                     - Otherwise, traverse to the right node.
             3. Get the majority class in said leaf.
        """
        if self._root is None:
            raise ValueError("Tree not fitted. Call 'fit' before 'predict'.")

        ###[TODO]: YOUR CODE HERE
        predictions = []

        for sample in X:
            node = self._root
            while node.split is not None:
                if sample[node.split.dim] <= node.split.pos:
                    node = node.left
                else:
                    node = node.right

            valid_labels = node.labels

            if not valid_labels:
                predictions.append(-1)
            else:
                majority_label = Counter(valid_labels).most_common(1)[0][0]
                predictions.append(majority_label)

        return np.array(predictions)

    def get_depth(self):
        """
        :return: The depth of the decision tree.
        """
        return self._root._get_depth()

    def _fit_tree(self, X, y, depth):
        """
        Recursive method to fit the decision tree.

        :param X: Numpy array with shape (num_samples, num_features)
        :param y: Numpy integer array with length num_samples
        :param depth: Current depth of the tree
        :return: A Node object representing the subtree rooted at this node

        Hint: to implement the prediction function, here are the steps:
             1. Check whether the current depth surpassed the limit.
                 - Return a leaf node when the limit is reached.
             2. Find the best split using the ```_find_best_split``` function.
             3. Check if the a valid split is found.
                 - If the function ```_find_best_split``` returns None, return a
                 leaf node.
             4. Find the left and right node using the splits.
             5. Return the node with left/right nodes.
        Note: 
             - Each node that is not a leaf, needs to have a `Split` object as attribute.
             - For leaf nodes, 'split' attribute needs to be 'None', and the `labels`
             attribute needs to be `y`.
        """

        ###[TODO]: YOUR CODE HERE

        if len(np.unique(y)) == 1:
            return Node(labels=y)

        if depth >= self.max_depth:
            return Node(labels=y)

        best_split = self._find_best_split(X, y)

        if best_split is None:
            return Node(labels=y)

        left_indices = X[:, best_split.dim] <= best_split.pos
        right_indices = X[:, best_split.dim] > best_split.pos

        left_node = self._fit_tree(X[left_indices], y[left_indices], depth + 1)
        right_node = self._fit_tree(X[right_indices], y[right_indices], depth + 1)

        node = Node(split=best_split, left=left_node, right=right_node)
        return node

    def _find_best_split(self, X, y):
        """
        Find the best split for the current node based on selected metric.

        :param X: Numpy array with shape (num_samples, num_features)
        :param y: Numpy integer array with length num_samples
        :return: A Split object representing the best split or None if no valid split is found

        In this function, you need to implement both Gini Impurity and Information Gain for
        two different modes.

        Hint: 
         - To implement this function, here are the steps:
             1. Use the `split_generator` function to generate splits given `X` and `y`.
             2. Calculate the score of the split using `_calculate_gini` and `_calculate_entropy`
             function.
             3. Return the best split.
         - If a split could not be found, return `None`.
         - If the given sample set only has 1 type of label, we don't need to split it.
        """
        
        best_split = None
        best_score = -np.inf if self.mode == "ig" else np.inf
        
        for split in split_generator(X, y):
            left_labels, right_labels = split.y_left, split.y_right
            
            if len(left_labels) == 0 or len(right_labels) == 0:
                continue
            
            if self.mode == "ig":
                left_entropy = self._calculate_entropy(left_labels)
                right_entropy = self._calculate_entropy(right_labels)
                p_left = len(left_labels) / len(y)
                p_right = len(right_labels) / len(y)
                info_gain = self._calculate_entropy(y) - (p_left * left_entropy + p_right * right_entropy)
                
                if info_gain > best_score:
                    best_score = info_gain
                    best_split = split
            
            elif self.mode == "gini":
                left_gini = self._calculate_gini(left_labels)
                right_gini = self._calculate_gini(right_labels)
                gini = (len(left_labels) / len(y)) * left_gini + (len(right_labels) / len(y)) * right_gini
                
                if gini < best_score:
                    best_score = gini
                    best_split = split
    
        return best_split

    def _calculate_gini(self, labels):
        """
        Calculate the Gini impurity of a set of labels.

        :param labels: Numpy integer array with length num_samples
        :return: Gini impurity
        """
        ###[TODO]: YOUR CODE HERE
        _, counts = np.unique(labels, return_counts=True)
        probabilities = counts / len(labels)
        gini = 1 - np.sum(probabilities ** 2)
        return gini

    def _calculate_entropy(self, labels):
        """
        Calculate the Entropy of a set of labels.

        :param labels: Numpy integer array with length num_samples
        :return: Entropy
        """
        ###[TODO]: YOUR CODE HERE
        _, counts = np.unique(labels, return_counts=True)
        probabilities = counts / len(labels)
        entropy = -np.sum(probabilities * np.log2(probabilities + 1e-9))
        return entropy


def tree_demo(mode):
    import draw_tree

    X = np.array([[0.88, 0.39], [0.49, 0.52], [0.68, 0.26], [0.57, 0.51], [0.61, 0.73]])
    y = np.array([1, 0, 0, 0, 1])
    tree = DecisionTree(mode=mode)
    tree.fit(X, y)
    draw_tree.draw_tree(X, y, tree)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Run a small demo to see if your code has any errors."
    )
    parser.add_argument(
        "--demo",
        metavar="N",
        type=str,
        help='Select a model to demo, "ig" for information gain, or "gini" for gini impurity.',
        default="ig",
    )

    args = parser.parse_args()
    tree_demo(args.demo)
