import { useState } from "react";
import axios from "axios";

function App() {
  const [prediction, setPrediction] = useState(null);
  const [loading, setLoading] = useState(false);

  const generateAndPredict = async () => {
    setLoading(true);
    try {
      const res = await axios.get("http://localhost:8000/generate-and-predict");
      setPrediction(res.data);
    } catch (err) {
      console.error(err);
      setPrediction({ error: "Something went wrong." });
    } finally {
      setLoading(false);
    }
  };

  return (
    <div style={{ padding: "2rem", fontFamily: "sans-serif" }}>
      <h1>💳 Credit Card Fraud Predictor</h1>
      <p>This app uses GPT + a trained model to simulate transactions and predict fraud in real-time.</p>
      <button onClick={generateAndPredict} disabled={loading}>
        {loading ? "Generating..." : "Generate & Predict"}
      </button>

      {prediction && (
        <div style={{ marginTop: "2rem" }}>
          <h3>🔍 Result</h3>
          {prediction.error ? (
            <p style={{ color: "red" }}>{prediction.error}</p>
          ) : (
            <>
              <p><strong>Fraud?</strong> {prediction.fraud ? "❗ Yes" : "✅ No"}</p>
              <pre style={{ background: "#f0f0f0", padding: "1rem" }}>
                {JSON.stringify(prediction.features, null, 2)}
              </pre>
            </>
          )}
        </div>
      )}
    </div>
  );
}

export default App;
