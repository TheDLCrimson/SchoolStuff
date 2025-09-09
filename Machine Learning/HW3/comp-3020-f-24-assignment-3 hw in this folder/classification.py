import numpy as np
import pandas as pd
import re
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.neural_network import MLPClassifier
from imblearn.over_sampling import SMOTE
from nltk.corpus import stopwords
from nltk.stem import PorterStemmer
import nltk
import matplotlib.pyplot as plt


nltk.download('stopwords')


def preprocess(x):
    
    x = re.sub(r'[^\w\s]', '', x)
    x = re.sub(r'\d+', '', x)
    
    x = x.lower().split()
    
    stop_words = set(stopwords.words('english'))
    x = [word for word in x if word not in stop_words]
    
    stemmer = PorterStemmer()
    x = [stemmer.stem(word) for word in x]
    
    return ' '.join(x)


train_data = pd.read_csv('data/train.csv')
train_data['text'] = train_data['text'].apply(preprocess)

y_train = train_data['labels'].tolist()
x_train = train_data['text']

X_train, X_val, y_train, y_val = train_test_split(x_train, y_train, test_size=0.3, random_state=1)

vectorizer = TfidfVectorizer(ngram_range=(1, 2), max_features=5000)
X_train_vectorized = vectorizer.fit_transform(X_train)
X_val_vectorized = vectorizer.transform(X_val)

smote = SMOTE(random_state=1)
X_train_resampled, y_train_resampled = smote.fit_resample(X_train_vectorized, y_train)

models = {
    "K-NN": KNeighborsClassifier(n_neighbors=5),
    "Decision Tree": DecisionTreeClassifier(max_depth=50, min_samples_split=5, min_samples_leaf=2, random_state=1),
    "Logistic Regression": LogisticRegression(max_iter=500, penalty='l2', dual=True , C=10.0, solver='liblinear', class_weight="balanced", random_state=1),
    "Neural Network": MLPClassifier(hidden_layer_sizes=(100,), max_iter=500, random_state=1)
}

for name, model in models.items():
    print(f"Training {name}...")
    model.fit(X_train_resampled, y_train_resampled)
    y_val_pred = model.predict(X_val_vectorized)
    print(f"Performance of {name} on Validation Set:")
    print(classification_report(y_val, y_val_pred))
    print("-" * 50)

def load_predict(file, vectorizer, model):
    
    test_data = pd.read_csv(file)
    test_data['input'] = test_data['input'].apply(preprocess)  
    
    vectorized_x = vectorizer.transform(test_data['input'])
    
    labels = model.predict(vectorized_x)
    return labels

best_model = models["Logistic Regression"]  
y_test = load_predict('data/test.csv', vectorizer, best_model)

result = pd.DataFrame({'id': range(len(y_test)), 'label': y_test})
result.to_csv('results.csv', index=False)
print("Predictions saved to 'results.csv'")

