import React, {useEffect, useState} from 'react';
import './styles.css';
import axios from '../../api/axios';
import {Post} from '../index'

export default function Feed( {userProfileFeed} ) {
    const [posts, setPosts] = useState([])
    const [numPosts, setnumPosts] = useState(0)

    var URL = "";
    if(userProfileFeed) {
        URL = "/Assignment4Backend/GetAllPosts?userID=" + sessionStorage.getItem('userID'); 
    } else {
        URL = "/Assignment4Backend/GetExplorePagePosts";
    }
    
    useEffect (() => {
        try {
        axios.get(URL).then((response) => {
            // console.log(response)
            setPosts(response.data);
            var count = response.data.length;
            setnumPosts(count);
        })
        } catch (err) {
        console.log(err)
        }
    },);

    const renderFeed = (
        <div>
            {
                posts.reverse().map((p, index) => {
                    return (
                        <div>
                            <Post key={index} rating={p.rating} date={p.date} name={p.name} text={p.text} image={p.image} postID={p.postID} userProfileFeed={userProfileFeed} />
                            <br />
                        </div>
                    )
                })
            }
        </div>
    )

    return (
        <div>
        {numPosts >>> 0 ? renderFeed : <div></div>}
        </div>
    );
    
};