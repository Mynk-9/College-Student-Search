function loadData() {
	var data = JSON.parse(query_results).qresults;
	var div = document.getElementsByClassName('result-stats')[0];
	div.innerHTML = 'Total ' + data.length + ' results generated';
	
	for (i = 0; i < data.length; i++) {
		var table = document.createElement("table");
		
		var row0 = table.insertRow(-1);
		var cell00 = row0.insertCell(0);
		cell00.innerHTML = "Name: ";
		var cell01 = row0.insertCell(1);
		cell01.innerHTML = data[i].N;
		
		var row1 = table.insertRow(-1);
		var cell10 = row1.insertCell(0);
		cell10.innerHTML = "ID No.: ";
		var cell11 = row1.insertCell(1);
		cell11.innerHTML = data[i].ID;
		
		var row2 = table.insertRow(-1);
		var cell20 = row2.insertCell(0);
		cell20.innerHTML = "Hostel/PS/Graduate: ";
		var cell21 = row2.insertCell(1);
		cell21.innerHTML = data[i].H;
		
		var row3 = table.insertRow(-1);
		var cell30 = row3.insertCell(0)
		cell30.innerHTML = "Room Number/PS Company: ";
		var cell31 = row3.insertCell(1);
		cell31.innerHTML = data[i].R;
		
		var row4 = table.insertRow(-1);
		var cell40 = row4.insertCell(0);
		cell40.innerHTML = "Social Media Data: ";
		var cell41 = row4.insertCell(1);
		cell41.innerHTML = data[i].SM;
		
		var row5 = table.insertRow(-1);
		var cell50 = row5.insertCell(0);
		cell50.innerHTML = "Image: ";
		var cell51 = row5.insertCell(1);
		var image = document.createElement("img");
		image.src = "Images Database\\" + data[i].ID.substring(0, 12) + ".jpg";
		cell51.appendChild(image);
		
		document.body.appendChild(table);
	}
}