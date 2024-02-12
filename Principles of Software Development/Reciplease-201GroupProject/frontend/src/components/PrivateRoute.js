import React from "react";
import { Redirect, Route, useLocation } from "react-router-dom";

//from https://www.sitepoint.com/react-router-complete-guide/

const PrivateRoute = ( { isUser, setisUser, userID, setuserID, component: Component } ) => {

    return (
        <Route>
            { sessionStorage.getItem('isUser') ?
                <Component isUser={isUser} setisUser={setisUser} userID={userID} setuserID={setuserID} />
            :
                <Redirect to='/login'/>
            }
        </Route>
    );
};
export default PrivateRoute;