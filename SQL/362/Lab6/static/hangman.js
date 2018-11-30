var count = 0

var guessed_letters = ""
var guesses = 0
var picture = 0
var wordbox = 0

var svgns="http://www.w3.org/2000/svg"

var words = ["diachronic", "lectionary", "banishes", "languishing", "leans", "compel", "sadly", "divider", "elevator", "boilers", "learn", "hayley", "boomed", "pickford", "flake", "skims", "littleneck", "ashley", "nods", "alfarome", "loans", "grayson", "crushed", "ocean", "counterbalance", "sanhedrin", "moderation", "viable", "underclassman", "salient", "inconsiderateness", "someplace", "sociometric", "antibiotic", "grew", "blister", "shoestring", "blinds", "hardest", "knickers", "laszlo", "sensible", "hurrying", "gut", "episodes", "suicidally", "weeds", "seeder", "current", "dignities", "shear", "tuxedo", "aperiodicity", "fleet", "shiloh", "barbudo", "mahogany", "intensifies", "backwards", "munster", "cavil", "avoidable", "obstacles", "equation", "alienation", "degrease", "warmth", "jousted", "modernness", "woeful", "allegiances", "peaceable", "critically", "volvo", "balsam", "divisors", "machines", "southey", "theking", "billabon", "selector", "honorableness", "vessels", "murre", "voids", "demote", "intertwined", "keystone", "curfew", "donkeys", "overpower", "postulate", "columnizing", "trollop", "audiotape", "confuser", "stipulate", "proctor", "inheritance", "coddington", "equivalents", "effects", "rays", "saffron", "qwerty", "godboy", "expresses", "baseboard", "cabdriver", "hymn", "midscale", "loots", "demure", "copiously", "trample", "cognac", "indoctrination", "repudiate", "bellingham", "contentment", "governor", "forbidden", "krakow", "slinging", "processing", "catastrophic", "dotes", "transcending", "engendering", "state", "dated", "rims", "excommunication", "break", "reek", "amphetamine", "crystals", "gravitational", "inventors", "inactivity", "transplanting", "thirtieth", "mistakion", "oxcart", "priory", "loner", "treacheries", "honesty", "towels", "strand", "deadlines", "burn", "paroled", "penumbra", "unplanned", "thankfulness", "bays", "tokyo", "cradles", "reeves", "theorist", "larvae", "abstinence", "boucher", "commences", "overtaker", "shotgun", "imprisonments", "recurrently", "metabolite", "cheerleaers", "advertises", "bombastic", "duplications", "greek", "dinnertime", "hardhat", "attributable", "beth", "housetop", "humors", "movers", "platform", "yeomanry", "kidde", "collinear", "chillingly", "spinneret", "parsonage", "epigrammatic"]

function reset_game()
{
	guesses = 0;
	guessed_letters = "";
	wordbox.innerHTML = "";
	draw_word()
}

function update_guessed_letters(letter)
{
	guessed_letters += letter
	var guess_box = document.getElementById("letters")
	var letNode = document.createTextNode(letter + " ")
	guess_box.appendChild(letNode)
}

function check_win()
{
	if (guesses > 10)
		return false
	for (i=0; i < words[count].length; ++i) {
		if (guessed_letters.includes(words[count][i]) == false)
			return false
	}
	return true
}


function draw_letter(i) {
	var letter = words[count][i]
	var letterNode = document.createTextNode(letter)
	var letterBox = document.createElement("div")

	letterBox.setAttribute("class", "guessedletter")

	letterBox.appendChild(letterNode)
	x = 20 + 80*i - words[count].length*80
	letterBox.style.transform = "translate(" + x + "px, -40px)"
	wordbox.appendChild(letterBox)
}

function draw_head() {
	var head = document.createElementNS(svgns, "circle")
	head.setAttributeNS(null, "r", "30")
	head.setAttributeNS(null, "cx", "80")
	head.setAttributeNS(null, "cy", "80")
	head.setAttributeNS(null, "fill", "none")
	head.setAttributeNS(null, "stroke", "black")
	head.setAttributeNS(null, "stroke-width", "4px")
	picture.appendChild(head)
}

function draw_torso() {
	var torso = document.createElementNS(svgns, "rect")
	torso.setAttributeNS(null, "width", "4px")
	torso.setAttributeNS(null, "height", "80px")
	torso.setAttributeNS(null, "x", "78")
	torso.setAttributeNS(null, "y", "110")
	torso.setAttributeNS(null, "fill", "black")
	picture.appendChild(torso)
}

function draw_arm(side) {
	var arm = document.createElementNS(svgns, "line")
	arm.setAttributeNS(null, "stroke", "black")	
	arm.setAttributeNS(null, "stroke-width", "2px")	
	arm.setAttributeNS(null, "fill", "none")
	arm.setAttributeNS(null, "x1", "80")
	arm.setAttributeNS(null, "y1", "130")
	arm.setAttributeNS(null, "y2", "120")
	if (side == "left") {
		arm.setAttributeNS(null, "x2", "48")
	}
	else {
		arm.setAttributeNS(null, "x2", "108")
	}
	picture.appendChild(arm)
}

function draw_leg(side) {
	var leg = document.createElementNS(svgns, "line")
	leg.setAttributeNS(null, "stroke", "black")	
	leg.setAttributeNS(null, "stroke-width", "2px")	
	leg.setAttributeNS(null, "fill", "none")
	leg.setAttributeNS(null, "x1", "80")
	leg.setAttributeNS(null, "y1", "190")
	leg.setAttributeNS(null, "y2", "220")
	if (side == "left") {
		leg.setAttributeNS(null, "x2", "48")
	}
	else {
		leg.setAttributeNS(null, "x2", "108")
	}
	picture.appendChild(leg)
}

function draw_eye(side) {
	var eye = document.createElementNS(svgns, "circle")
	eye.setAttributeNS(null, "stroke", "blue")
	eye.setAttributeNS(null, "stroke-width", "2px")
	eye.setAttributeNS(null, "fill", "none")
	eye.setAttributeNS(null, "r", "4px")
	eye.setAttributeNS(null, "cy", "75")
	if (side == "left") {
		eye.setAttributeNS(null, "cx", "70")
	}
	else {
		eye.setAttributeNS(null, "cx", "90")
	}
	picture.appendChild(eye)
}

function draw_mouth() {
	var mouth = document.createElementNS(svgns, "circle")
	mouth.setAttributeNS(null, "stroke", "red")
	mouth.setAttributeNS(null, "stroke-width", "2px")
	mouth.setAttributeNS(null, "fill", "none")
	mouth.setAttributeNS(null, "r", "4px")
	mouth.setAttributeNS(null, "cy", "95")
	mouth.setAttributeNS(null, "cx", "80")
	picture.appendChild(mouth)
}

function draw_nose() {
	var nose = document.createElementNS(svgns, "polyline")
	nose.setAttributeNS(null, "stroke", "black")
	nose.setAttributeNS(null, "stroke-width", "2px")
	nose.setAttributeNS(null, "fill", "none")
	nose.setAttributeNS(null, "points", "82,85 78,85 78,80")
	picture.appendChild(nose)
}

var imgNode = 0
var root = 0
var start = 0

function load_game()
{
	picture = document.getElementById("gallows")
	wordbox = document.getElementById("contents")
	draw_word()

	document.body.addEventListener("keypress", handle_guess)
}

function draw_word()
{
	for (i=0; i < words[count].length; ++i)
	{
		var image = document.createElement("img")
		image.src = "Tile.png"
		wordbox.appendChild(image)
		
	}
}

function draw_next_body_part()
{
	if (guesses == 0)
	{
		draw_head()
	}
	else if (guesses == 1)
	{
		draw_torso()
	}
	else if (guesses == 2)
	{
		draw_arm("left")
	}
	else if (guesses == 3)
	{
		draw_arm("right")
	}
	else if (guesses == 4)
	{
		draw_leg("left")
	}
	else if (guesses == 5)
	{
		draw_leg("right")
	}
	else if (guesses == 6)
	{
		draw_eye("left")
	}
	else if (guesses == 7)
	{
		draw_eye("right")
	}
	else if (guesses == 8)
	{
		draw_nose()
	}
	else if (guesses == 9)
	{
		draw_mouth()
	}
}

function handle_guess(event)
{
	var letter = String.fromCharCode(event.which)
	if (guessed_letters.includes(letter)) {
		return
	}

	update_guessed_letters(letter)

	var found = false
	for (i=0; i < words[count].length; ++i) {
		if (letter == words[count][i]) {
			draw_letter(i)
			found = true
		}
	}
	if (found != true) {
		if (guesses >= 10) {
			alert("You're hung!  Try again!")
			++count;
			reset_game();
		}
		else {
			draw_next_body_part()
			++guesses;
		}
	}
	if (check_win()) {
		alert("Congratulation!  You win!")
		++count;
		reset_game();
	}
}

