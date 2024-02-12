import React from 'react';
import ReactDOM from 'react-dom/client';
import './mainStyles.css';
import { BrowserRouter as Router } from 'react-router-dom';
import { AuthProvider } from './components';

// import { UnregisteredLandingPage } from './pages';
import App from './pages/App/App';



const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
    // <AuthProvider >
        <Router>
            <App />
        </Router>
    // </AuthProvider>
);
