from fastapi import FastAPI
from pydantic import BaseModel
import joblib
import numpy as np
import openai
import os
from dotenv import load_dotenv
load_dotenv()

app = FastAPI()
model = joblib.load("model/model.pkl")

class Transaction(BaseModel):
    features: list[float]

@app.post("/predict")
def predict(transaction: Transaction):
    X = np.array(transaction.features).reshape(1, -1)
    if X.shape[1] != 30:
        return {"error": "Exactly 30 features are required."}
    prediction = model.predict(X)
    return {"fraud": bool(prediction[0])}

from openai import OpenAI

client = OpenAI(api_key=os.getenv("OPENAI_API_KEY"))

@app.get("/generate-and-predict")
def generate_and_predict():
    prompt = (
        "Generate a list of 30 numeric features (floats), "
        "including realistic Time, Amount, and V1-V28 values "
        "for a credit card fraud detection model. "
        "Respond only with a valid Python list of 30 float numbers."
    )

    try:
        response = client.chat.completions.create(
            model="gpt-3.5-turbo",
            messages=[{"role": "user", "content": prompt}],
            temperature=0.7
        )

        content = response.choices[0].message.content
        features = eval(content)

        if len(features) != 30:
            return {"error": "GPT did not return 30 features.", "raw_output": content}

        X = np.array(features).reshape(1, -1)
        prediction = model.predict(X)

        return {
            "features": features,
            "fraud": bool(prediction[0])
        }

    except Exception as e:
        return {"error": str(e)}
