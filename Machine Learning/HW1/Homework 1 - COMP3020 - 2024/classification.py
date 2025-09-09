import pandas as pd
import numpy as np
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from k_nearest_neighbors import KNNClassifier
from decision_tree import DecisionTree
import matplotlib.pyplot as plt

if __name__ == "__main__":
    """
        For this exercise, you will be loading and training the models
        you implemented, that being K-nearest neighbors and Decision tree.
        
        You are given the Water Quality and Potability dataset, the main
        goal of which is to predict whether or not the drink sample is Potable
        or not.
        
        You are provided with two subsets:
             - Training dataset -  to train the model.
             - Validation datasest - to validate the model after training.
        
        To earn points for this exercise, you need to:
            1. Load the datasets and preprocess it.
            2. Train the model.
            3. Demonstrate overfiting and underfiting through the training and 
            validation results. This can be done by:
                - Show different results using different hyper-parameters.
                - Plot out the changes between training and validation accuracy
                when increasing certain hyper-parameters.
        
        If you find it difficult to get started, please follow the tutorial
        given in the ```classification_tutorial.ipynb``` notebook.
    """
    
    train_df = pd.read_csv("./dataset/train.csv")
    val_df = pd.read_csv("./dataset/val.csv")
    
    train_df["TRN_TYPE"] = train_df["TRN_TYPE"].replace(0, np.nan)
    val_df["TRN_TYPE"] = val_df["TRN_TYPE"].replace(0, np.nan)

    train_df = train_df.dropna(subset=["TRN_TYPE"])
    val_df = val_df.dropna(subset=["TRN_TYPE"])

    le = preprocessing.LabelEncoder()
    combined_labels = pd.concat([train_df["TRN_TYPE"], val_df["TRN_TYPE"]])
    le.fit(combined_labels)

    train_df['TRN_TYPE'] = le.transform(train_df["TRN_TYPE"])
    val_df['TRN_TYPE'] = le.transform(val_df["TRN_TYPE"])

    print(f"List of unique elements: {le.classes_}")
      
    train_df = train_df.fillna(0)
    val_df = val_df.fillna(0)
    
    label_column = "TRN_TYPE"
    X_train = train_df.loc[:, train_df.columns != label_column]
    y_train = train_df[label_column]
    
    X_val = val_df.loc[:, val_df.columns != label_column]
    y_val = val_df[label_column]
      
    X_train = X_train.to_numpy()
    y_train = y_train.to_numpy()
    X_val = X_val.to_numpy()
    y_val = y_val.to_numpy()
       
    def plot_accuracies(train_accuracies, val_accuracies, param_name, param_values):
        plt.plot(param_values, train_accuracies, label="Train Accuracy", marker='o')
        plt.plot(param_values, val_accuracies, label="Validation Accuracy", marker='o')
        plt.xlabel(param_name)
        plt.ylabel('Accuracy')
        plt.title(f"Train vs Validation Accuracy ({param_name})")
        plt.legend()
        plt.grid(True)
        plt.show()
    
    train_accuracies_tree = []
    val_accuracies_tree = []
    depth_values = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15]
    
    for depth in depth_values:
        tree = DecisionTree(max_depth=depth, mode="ig")
        tree.fit(X_train, y_train)

        y_train_pred_tree = tree.predict(X_train)
        train_accuracy_tree = accuracy_score(y_train, y_train_pred_tree)
       
        y_val_pred_tree = tree.predict(X_val)
        val_accuracy_tree = accuracy_score(y_val, y_val_pred_tree)
    
        train_accuracies_tree.append(train_accuracy_tree)
        val_accuracies_tree.append(val_accuracy_tree)
     
    plot_accuracies(train_accuracies_tree, val_accuracies_tree, "Max Depth (Decision Tree)", depth_values)
       
    train_accuracies_knn = []
    val_accuracies_knn = []
    k_values = [1, 3, 5, 7, 9, 11, 21, 23, 25, 27, 27, 31, 33, 35, 37, 39, 41, 43, 45, 69]
    
    for k in k_values:
        knn = KNNClassifier(k=k)
        knn.fit(X_train, y_train)
    
        y_train_pred_knn = knn.predict(X_train)
        train_accuracy_knn = accuracy_score(y_train, y_train_pred_knn)
     
        y_val_pred_knn = knn.predict(X_val)
        val_accuracy_knn = accuracy_score(y_val, y_val_pred_knn)
    
        train_accuracies_knn.append(train_accuracy_knn)
        val_accuracies_knn.append(val_accuracy_knn)
    
    plot_accuracies(train_accuracies_knn, val_accuracies_knn, "K (KNN Classifier)", k_values)

    explanation_text = """

    ***PLEASE CHECK THE classification.ipynb file instead of this file.***

    ##### Concept:

    **Underfitting** happens when a model is too simple, resulting in poor performance on both training and validation data. 
    As shown in the plots, low depth for Decision Tree or high K for KNN.

    **Overfitting** occurs when a model is too complex, achieving high training accuracy but poor validation accuracy. 
    As shown in the plots, high depth for Decision Tree or very low K for KNN.

    ##### Form the results:

    **Decision Tree**: Overfitting starts after max_depth=6. Balanced model around max_depth=4-6.

    **KNN**: Overfitting at k=1. Balanced model around k=10-20.

    These balanced regions show where the models generalize best without memorizing the training data.
        """
    
    print(explanation_text)
    