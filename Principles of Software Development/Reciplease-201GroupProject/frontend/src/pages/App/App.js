import './App.css';
import React, { useState } from 'react';
import { Switch, Route} from 'react-router-dom'
import { LoginPage, ExplorePage, SearchPage, NewPostPage, FollowingPage, MessagesPage, UserProfilePage } from '../../pages'
import { BackToTopButton, NavBar, PrivateRoute } from '../../components';
import { RegisterPage } from '../index';

export default function App() {
    const [isUser, setisUser] = useState(false)
    const [userID, setuserID] = useState(-1);
    
    return (
        <div>
        <div><NavBar isUser={isUser} userID={userID} ></NavBar></div>    
            
        

        <Switch>
            <Route exact path="/">
                <ExplorePage/>
            </Route>
            <Route exact path="/search">
                <SearchPage/>
            </Route>
            <Route exact path="/login">
                <LoginPage isUser={isUser} setisUser={setisUser} userID={userID} setuserID={setuserID}/>
            </Route>
            <PrivateRoute exact path="/following" isUser={isUser} userID={userID} component={FollowingPage} />
            <PrivateRoute exact path="/newpost" isUser={isUser} userID={userID} component={NewPostPage} />
            <PrivateRoute exact path="/messages" isUser={isUser} userID={userID} component={MessagesPage} />
            <Route exact path="/register">
                <RegisterPage isUser={isUser} setisUser={setisUser} userID={userID} setuserID={setuserID}/>
            </Route>
            <PrivateRoute exact path="/userprofile" isUser={isUser} setisUser={setisUser} userID={userID} component={UserProfilePage}/>
        </Switch>
        <BackToTopButton />
        </div>
    );
}