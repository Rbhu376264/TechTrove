import './navbar.css';
import React from "react";
import { NavBarReg, NavBarUnreg } from '..';

export default function NavBar( {isUser, userID} ) {
    // const isAuth = sessionStorage.getItem('isUser')
    // if(!isUser && userID === -1) {
    if(sessionStorage.getItem('isUser')) {
        return <NavBarReg/>
        
    } 
    return <NavBarUnreg/>
}