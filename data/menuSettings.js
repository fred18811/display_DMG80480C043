import {helpFunctions} from "./helpfunctions.js";

export const menuSetings = (props)=> {
    const cnt = helpFunctions.parsingHTMLElements(`
    <div>
        <label>x:<input type="number"></lablel>
        <label>y:<input type="number"></lablel>
    </div>
    `)

    return cnt
} 

