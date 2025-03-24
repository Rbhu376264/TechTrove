from preprocessing import preprocess_data
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report
import joblib
import os

def train_and_save_model():
    X_train, X_test, y_train, y_test = preprocess_data()

    model = RandomForestClassifier(n_estimators=100, random_state=42)
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    print("Classification Report:\n", classification_report(y_test, y_pred))

    os.makedirs("model", exist_ok=True)
    joblib.dump(model, "model/model.pkl")
    print("Model saved to model/model.pkl")

if __name__ == "__main__":
    train_and_save_model()
