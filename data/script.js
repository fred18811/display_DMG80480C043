import {helpFunctions} from "./helpfunctions.js";
import {menuSetings} from "./menuSettings.js";

const body = document.querySelector("body");

// struct Ligth {
//    int16_t x; 
//    int16_t y; 
//    int16_t width; 
//    int16_t height;
//    int16_t radius;  
//    int color_on;
//    int color_off;
// };

// struct Button {
//    int16_t x; 
//    int16_t y; 
//    int16_t width; 
//    int16_t height;
//    int16_t radius;  
//    int color; 
//    int16_t text_x; 
//    int16_t text_y; 
//    uint8_t size_text; 
//    int color_text;
//    const char *name_text;
//    bool color_ligth;
//    Ligth ligth[10];
// };


const main = (props)=>{
    const {
        bkgrd,
        swbtn
    } = props;

    const dataDisplay = {
        bkgrd:""
    };

    function changeColor (e){
        dataDisplay.bkgrd = e.target.value;
        main.querySelector('div[panelContent=""]').style.background = e.target.value;
    }



    const main = helpFunctions.parsingHTMLElements(`
    <div class="edit-form edit-form-row" style="background:white; height:100%">
        <div class="edit-form edit-form-position-center edit-form-align-position-center edit-form-column" style="width:100%;">
            <div class="width_480">
                <div class="edit-form-width-100 edit-form" contSettings>
                    <input type="color" value="${bkgrd}">
                </div>
                <div class="panel-rgb position-relative" style="background:${bkgrd};" panelContent></div>
            </div>
        </div>
        <div style="margin-left: auto;" panelBtn>
        </div>
    </div>
    `);   
    main.querySelector('div[contSettings=""]').append(menuSetings()
)
    main.querySelector('input[type="color"]').addEventListener("change",(e)=>changeColor(e));
    main.querySelector('div[panelBtn=""]').append(switchButton(main.querySelector('div[panelContent=""]')));

    (swbtn.length)?swbtn.forEach(i=>main.querySelector('div[panelContent=""]').append(switchButtonContent(i))):"";

    return main
}


const req = fetch(`/display.json`)
    req
    .then(response=>response.json())
    .then(answ => {
        body.append(main(answ));
    });

//////////////////////////////////////////////////////////
//кнопак переключения на панель
function switchButton (props) {

    function makeCopy (obj){
        obj.append(switchButtonContent())
    }

    const btn = document.createElement("input");
    btn.value = "Кнопка";
    btn.type = "button";
    btn.classList = "button-select";
    btn.addEventListener("click",()=>makeCopy(props));
    return btn;
}

////////
//Контент кнопаки переключения   
function switchButtonContent (props) {
    const btn = helpFunctions.parsingHTMLElements(`
            <div btnConent style="width:${props.wdt}px; height:${props.hgt}px;background:${props.clr};left:${props.x}px;top:${props.y}px; border-radius:${props.rds}px" class="no-margin position-absolute">
                <h1 class="no-margin position-absolute" style="left:${props.txt_x}px; top:${props.txt_y}px; font-size:${props.sz_txt}px; color:${props.clr_txt};">${props.nm_txt}</h1>
            </div>
            `);
    
    //Наведение
    btn.addEventListener("mouseover",(e)=>mouseOverOut(e));
    btn.querySelector("h1").addEventListener("mouseover",(e)=>mouseOverOut(e));
    //Мышь в не поля
    btn.addEventListener("mouseout",(e)=>mouseOverOut(e));
    btn.querySelector("h1").addEventListener("mouseout",(e)=>mouseOverOut(e));

    //Выбор
    btn.addEventListener("click",(e)=>selecetObject(e));
    btn.querySelector("h1").addEventListener("click",(e)=>selecetObject(e));

    //Перенос
    btn.addEventListener("dragstart",(e)=>dragstart(e));
    btn.querySelector("h1").addEventListener("dragstart",(e)=>dragstart(e));



    (props.lgths.length)? props.lgths.forEach(i=>btn.append(switchButtonLigth(i,props.bool_clr_lgt))) :"";
    return btn;
}

//Контент свет для кнопки
function switchButtonLigth (props,ligth) {
    const lgt = helpFunctions.parsingHTMLElements(`<div class="no-margin position-absolute" style="width:${props.wdt}px; height:${props.hgt}px;background:${(ligth)?props.color_on:props.color_off};left:${props.x}px;top:${props.y}px; border-radius:${props.rds}px"></div>`);
    
    lgt.addEventListener("mouseover",(e)=>mouseOverOut(e));
    lgt.addEventListener("mouseout",(e)=>mouseOverOut(e));
    
    lgt.addEventListener("click",(e)=>selecetObject(e));
    
    lgt.addEventListener("dragstart",(e)=>dragstart(e));
    return lgt;
}
//////////////////////////////////////////////////////////////////


function dragstart(e) {
    console.log(e.target)
//   // Меняем цвет на фиолетовый
//   e.target.classList.add("item--hold");
//   // Удаляем элемент из бокса
//   setTimeout(() => e.target.classList.add("item--hide"), 0);
}

function mouseOverOut(e) {
    e.type === "mouseover"? e.target.classList.add("select"):e.target.classList.remove("select");
}

function selecetObject(e) {
    e.type === "mouseover"? e.target.classList.add("select"):e.target.classList.remove("select");
    console.log(e.target)
}
