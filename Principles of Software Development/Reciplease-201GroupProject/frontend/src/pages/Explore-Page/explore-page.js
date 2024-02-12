import { Feed, Post } from '../../components';
import React, {useEffect, useState} from 'react';
import './styles.css';
import axios from '../../api/axios';


export default function ExplorePage( ) {


    return (
        <div className="explore">

            <Feed id="explore-feed"/>

        </div>
    );
}

