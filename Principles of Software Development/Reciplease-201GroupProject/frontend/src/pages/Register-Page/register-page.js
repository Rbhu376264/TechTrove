import { useState, useEffect } from 'react';
import { Link, Redirect } from 'react-router-dom';
import axios from '../../api/axios';
import './styles.css';
import { ExplorePage } from '../../pages'

export default function RegisterPage( {isUser, setisUser, userID, setuserID} ) {

	// States for registration
	const [user, setUser] = useState('');
	const [password, setPassword] = useState('');
	const [hint, setHint] = useState('');


	// States for checking the errors
	const [submitted, setSubmitted] = useState(false);
	const [error, setError] = useState(false);

	// Update userID when user is authenticated
	useEffect(() => {
        if(userID !== -1) {
			sessionStorage.setItem('userID', userID)
            sessionStorage.setItem('isUser', true)
            sessionStorage.setItem('username', user)
            setUser('')
            setPassword('')
			setHint('')
            setisUser(true);
			setSubmitted(true)
			setError(false)
            console.log('update isUser', isUser)
        }
    }, [userID]);
	
	// Handling the form submission
	const handleSubmit = async (e) => {
		e.preventDefault();

		const data = {
			userName: user,
			password: password,
			hint: hint,
			profileImage: '',
			bio: ''
		}

		try {
			const URL = "/Assignment4Backend/RegisterUser?userName=" + user + "&password=" + password + "&hint=" + hint + "&profileImage=" + '' + "&bio=" + '' + "&rating=" + '0';
			//+ "&profileImage=/'/'&bio=/'/'"
			const response = await axios.post(URL, data, {
				headers: {
					'Content-Type': 'application/json',
                    'Access-Control-Allow-Origin': "*",
				}
			})
			.then((response) => {
				console.log(response)
				setuserID(response.data.userID)
			});


		} catch (err) {
			console.log(err.response?.status)
		}

	};

	// Showing success message
	const successMessage = () => {
		return (
			<div
				className="success"
				style={{
					display: submitted ? '' : 'none',
				}}>
				<h1>User {user} successfully registered!!</h1>
			</div>
		);
	};

	// Showing error message if error is true
	const errorMessage = () => {
		return (
			<div
				className="error"
				style={{
					display: error ? '' : 'none',
				}}>
				<h1>Please enter all the fields</h1>
			</div>
		);
	};

	const renderForm = (
		<div className="form">
			<div class="header">
				<h1> Register</h1>
			</div>

			{/* Calling to the methods */}
			<div className="messages">
				{errorMessage()}
			</div>

			<form onSubmit={handleSubmit}>
				{/* Labels and inputs for form data */}
				<div className="input-container">
                    <label htmlFor="user">Username </label>
                    <input 
                        type="text" 
                        name="userName" 
                        onChange={(e) => setUser(e.target.value)} 
                        value={user}
                        required 
                    />
					{errorMessage()}
                </div>
				<div className="input-container">
                    <label htmlFor="user">Password </label>
                    <input 
                        type="text" 
                        name="password" 
                        onChange={(e) => setPassword(e.target.value)} 
                        value={password}
                        required 
                    />
					{errorMessage()}
                </div>
				<div className="input-container">
                    <label htmlFor="user">Password Hint </label>
                    <input 
                        type="text" 
                        name="hint" 
                        onChange={(e) => setHint(e.target.value)} 
                        value={hint}
                        required 
                    />
					{errorMessage()}
                </div>
				<div className="button-container">
					<input type="submit" />
					<div className="space"></div>
                    <Link exact="true" to="/login">
                        <button type = "register">Login</button>
                    </Link>
				</div> 
				{successMessage()}
			</form>
		</div>
	);

	return (
		<div>
        {isUser ? <div><ExplorePage/></div> : renderForm}
        </div>
	);
}
