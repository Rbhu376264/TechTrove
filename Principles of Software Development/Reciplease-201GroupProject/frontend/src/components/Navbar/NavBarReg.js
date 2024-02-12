import './navbar.css';
import React from "react";
import { Link } from "react-router-dom";

export default function NavBarReg() {
  return (
    <div className="navbar">
      {/* <h1>ReciPlease</h1> */}
      <nav>
        <div id="left-reg">
          <img src={require("../../assets/Recipes.png")} alt="Cook book logo" id="logo"></img>
          <Link exact="true" to="/" style={linkStyles_left} className="link">Explore</Link>
          {/* <Link exact="true" to="/following" style={linkStyles_left} className="link">Following</Link> */}
        </div>
        <div id="middle-reg">
          {/* <Link exact to="/search" style={linkStyles_search}><input type='text' placeholder='search' id='search-bar'/></Link> */}
          <Link exact="true" to="/search" style={linkStyles_middle} className="link">Search</Link>
        </div>
        <div id="right-reg">
          <Link exact="true" to="/newpost" style={linkStyles_right} className="link">New Post</Link>
          <Link exact="true" to="/messages" style={linkStyles_right} className="link">Messages</Link>
          <Link exact="true" to="/userprofile" style={linkStyles_right} className="link">Profile</Link>
        </div>

      </nav>
    </div>

  );
}

const linkStyles_left = {
  color: 'black',
  textDecoration: 'none',
  fontSize: '20px',
  verticleAlign: 'middle',
};

const linkStyles_middle = {
  color: 'black',
  textDecoration: 'none',
  fontSize: '20px',
  marginLeft: '7em',
};

const linkStyles_right = {
  color: 'black',
  textDecoration: 'none',
  fontSize: '20px',
};
