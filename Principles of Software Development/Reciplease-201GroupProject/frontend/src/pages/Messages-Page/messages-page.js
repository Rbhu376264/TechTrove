import { useEffect, useState } from 'react';
import './styles.css';

export default function MessagesPage( props ) {
    const [messages, setMessages] = useState([]);
    const [inputValue, setValue] = useState("");
    const [ws, setWS] = useState(null);

    useEffect(() => {
        setWS(new WebSocket("ws://localhost:3456/Assignment4Backend/ws"));
    }, []);

    useEffect(() => {
        if(ws != null){
            ws.onopen = (event) => {
                console.log("Connected");
            };
            ws.onmessage = function (event) {
                setMessages(messages => [...messages, event.data]);
            };
            //return () => ws.close();
            ws.onclose = function(event) {
                console.log(event.data);
            }
        }

    }, [ws]);

    
    
    const sendMessage = () => {
        ws.send(sessionStorage.getItem('username') + ": " + inputValue);
    }


    return (
        <div className='messages-page'>
            <form name="chatform" className="chat-form">
                <input type="text" id="send-field" name="message" value={inputValue} onChange={event => setValue(event.target.value)} required /><br />
                <input type="button" id="send-button" value="Send Message" onClick={sendMessage} />
                <br />
            </form>
            <div className='messages'>
                <br/>
            {
                messages.map(message => {
                    //style this:
                    return <p id="p">{message}</p>
                })
            }
            </div>

        </div>
    );
}
