import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from imblearn.over_sampling import SMOTE

def load_data():
    return pd.read_csv("data/creditcard.csv")

def preprocess_data():
    df = load_data()
    X = df.drop("Class", axis=1)
    y = df["Class"]

    # Step 1: Scale features first
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)

    # Step 2: Split into train/test BEFORE SMOTE
    X_train, X_test, y_train, y_test = train_test_split(
        X_scaled, y, test_size=0.2, random_state=42, stratify=y
    )

    # Step 3: Apply SMOTE only on training data
    smote = SMOTE(random_state=42)
    X_train_resampled, y_train_resampled = smote.fit_resample(X_train, y_train)

    return X_train_resampled, X_test, y_train_resampled, y_test

# def preprocess_data():
#     df = load_data()
#     X = df.drop("Class", axis=1)
#     y = df["Class"]

#     scaler = StandardScaler()
#     X_scaled = scaler.fit_transform(X)

#     smote = SMOTE()
#     X_resampled, y_resampled = smote.fit_resample(X_scaled, y)

#     return train_test_split(X_resampled, y_resampled, test_size=0.2, random_state=42)
