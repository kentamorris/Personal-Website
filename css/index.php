<?php

$to = 'kenta.morris@gmail.com';
$subject = 'From kentamorris.net16.net';

$name = $_POST['name'];
$email = $_POST['email'];
$message = $_POST['message'];

$message = <<<EMAIL

name: $name
email: $email

$message


EMAIL;

$header = '$email';

if($_POST){
mail($to, $subject, $message, $header);
$feedback = 'Your message has been sent';
}

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<!--cira-->
<html>

<head>
    <title>Kenta Morris - General Purpose Website</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link rel="stylesheet" type="text/css" href="css/style.css"/>
</head>

<body >
    
    <div id="home">a</div>
    <div id="menu"></div>
    <div class="logo"><a>K. Morris'</a><p>personal website</p></div>
    <a href="#home"><div class="box fade-in one">Home</div></a> 
    <a href="#about"><div class="box fade-in two">About</div></a> 
    <a href="#projects"><div class="box fade-in three">Projects</div></a>
    <a href="#resume"><div class="box fade-in four">Resume</div></a>
    <a href="#contact"><div class="box fade-in five">Contact</div></a>
    
    <div class="container home">
        <h1>HELO!</h1>
        <p>My name is Kenta Morris. This is a website I created using HTML and CSS to display my coding abilities. It should also give insight into who I am.</p><p>Feel free to look around!</p>
    </div>    
    
    <div id="about" class="container about">
        <div class="textBox">
        <h1>About me</h1>
        <p>I am currently a first year Mechatronics Engineering Student at the University of Waterloo, living on campus.</p><p> My hometown is Ottawa, however much of my extended family lives in the Greater Toronto Area. I have traveled to England and most recently Japan and I love experiencing what a new city or country has to offer.</p><p>In my free time I also enjoy camping and team sports such as soccer and hockey.</p>
        </div> 
    </div>   
    
    <div id="projects" class="container projects">
        <div class="textBox">
        <h1>Projects</h1>
            <p>I currently only have one project other than this website, however I hope to countinue developing new ideas throughout my University experience.</p><p><b>AlgoRhyme</b> was a c program developed by me and classmate in my senior year of highschool. Its purpose is to generate random rhyming sentences by analyising the pronouciation and word class of a selected words and using pre-set sentence syntax. Feel free to download our the c files by clicking <a href="downloads/AlgoRyhme.zip">here</a>.</p>
        </div>
    </div>   
    <div id="resume" class="container resume">
        <div class="container paper1">
            <h1>My Resume</h1>
            <p>Here I have my general resume, intended for potential employers looking to hire for me for a coop term.</p>
        </div>
        <div class="container paper2">
            <a href="downloads/KMorris_Resume_June2016.pdf" target="_blank">click here to dowload the pdf</a>
        </div>
    </div> 
    
    <div id="contact" class="contact">
        <h1>Contact Me</h1>
        <p>Feel free to send me a message. Leave your email and so I can get answer as soon as possible.</p>
        <p id="feedback"><?php echo $feedback; ?></p>
        <form action="?#contact" method="post">
            <ul>
                    <label for="name">Name:</label>
                    <input type="text" name="name" id="name" />
                    <label for="email">Email:</label>
                    <input type="text" name="email" id="email" />
                    <label for="message">Message:</label>
                    <textarea id="message" name="message" cols="42" rows="9"></textarea>
                    <input type="submit" value="Submit"/>
            </ul>
        </form>
    </div> 
</body>


</html>