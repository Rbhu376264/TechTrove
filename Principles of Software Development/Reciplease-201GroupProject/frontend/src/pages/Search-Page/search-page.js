import { useState } from 'react';
import './styles.css';
import axios from '../../api/axios';
import {Post} from '../../components'

export default function SearchPage( ) {

	// States for registration
	const [search, setSearch] = useState('');
	const [noResult, setnoResult] = useState(false);

	// States for checking the errors
	const [submitted, setSubmitted] = useState(false);
	const [error, setError] = useState(false);

	// Handling the name change
	const handleSearch = (e) => {
		setSearch(e.target.value);
		setSubmitted(false);
	};

	const [posts, setPosts] = useState([])

	const handleSubmit = async (e) => {
		e.preventDefault();
		if(search === '') {
			setError(true);
			window.alert("Please enter a search term");
		} else {
			try {
				const URL = "/Assignment4Backend/GetPostsByKey?keyWord=" + search;
				axios.get(URL).then((response) => {
					console.log(response)
					if(response.data.length === 0) { setnoResult(true); setSearch('') }
					setPosts(response.data);
					setSubmitted(true)
					renderFeed()
				})
				setnoResult(false)
					
			} catch (err) {
				console.log(err.response?.status)
				window.alert('search error')

			} 
		}
	}

    const renderFeed = (
        <div>
            {
                posts.map((p, index) => {
                    return (
                        <div>
                            <Post key={index} rating={p.rating} date={p.date} name={p.name} text={p.text} image={p.image} postID={index} />
                            <br />
                        </div>
                    )
                })
            }
        </div>
	)

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
	const noResultMessage = () => {
		return (
			<div
				className="error"
				style={{
					display: noResult ? '' : 'none',
				}}>
				<h1>No posts with that search term.</h1>
			</div>
		);
	};

	return (
		<div className="form">
			<div class="header">
				<h1> Search</h1>
			</div>

			{/* Calling to the methods */}
			<div className="messages">
				{errorMessage()}
			</div>

			<form onSubmit={handleSubmit}>
				{/* Labels and inputs for form data */}
				<div className="input-container">
                    <label> Enter a Term </label>
                    <input type="search" name="search" onChange={handleSearch} value={search} required />
                    {errorMessage()}
                </div>
				<div className="button-container">
					<input type="submit" />
				</div> 
				<div id="search-feed">
					{submitted ? renderFeed : <div></div>}
				</div>
			</form>
			{noResultMessage()}
		</div>
	);
}
