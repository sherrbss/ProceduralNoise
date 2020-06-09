/**
 * PrimePlot.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * An implementation of primes plotted as polar coordinates.
 */

#include "PrimePlot.h"

bool PrimePlot::isPrime(int val) {

    for (int i = 2; i*i <= val; i++) {
        if (val % i == 0) {
            return false;
        }
    }

    return true;
}

/*
 * Output SVG header.
 */
void PrimePlot::headerSVG(std::ofstream& outfile, int width, int height, std::string file) {

    std::string svgHeaderPart1="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
                               "<!-- Created with CurveBenchmark -->\n"
                               "<svg\n"
                               "    xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
                               "    xmlns:cc=\"http://creativecommons.org/ns#\"\n"
                               "    xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                               "    xmlns:svg=\"http://www.w3.org/2000/svg\"\n"
                               "    xmlns=\"http://www.w3.org/2000/svg\"\n"
                               "    xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n"
                               "    xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\n"
                               "    width=\"";
    std::string svgHeaderPart2="\"\n"
                               "    height=\"";
    std::string svgHeaderPart3="\"\n"
                               "    id=\"svg2\"\n"
                               "    version=\"1.1\"\n"
                               //		"    inkscape:version=\"0.48.1 r9760\"\n"
                               "    sodipodi:docname=\"";
    std::string svgHeaderPart4 = "\">\n"
                                 "<defs\n"
                                 "    id=\"defs4\" />\n"
                                 "<metadata\n"
                                 "    id=\"metadata7\">\n"
                                 "    <rdf:RDF>\n"
                                 "        <cc:Work\n"
                                 "            rdf:about=\"\">\n"
                                 "            <dc:format>image/svg+xml</dc:format>\n"
                                 "            <dc:type\n"
                                 "                rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\" />\n"
                                 "            <dc:title></dc:title>\n"
                                 "        </cc:Work>\n"
                                 "    </rdf:RDF>\n"
                                 "</metadata>\n"
                                 "<g\n"
                                 "    inkscape:label=\"Layer 1\"\n"
                                 "    inkscape:groupmode=\"layer\"\n"
                                 "    id=\"layer1\">\n";

    outfile << svgHeaderPart1 << width << svgHeaderPart2 << height << svgHeaderPart3 << file << svgHeaderPart4 << std::endl;
}

/*
 * Output SVG footer.
 */
void PrimePlot::footerSVG(std::ofstream& outfile) {
    std::string svgFooter = "    </g>\n"
                            "</svg>";

    outfile << svgFooter << std::endl;
}

/*
 * Saves image as SVG file, if enabled in driver.
 *
 * Parameters:
 *      points: Vector of point structs
 *      writeBMP: 0 being do no create BMP and 1 being create BMP
 *      width: pixels in x-dimension
 *      height: pixels in y-dimension
 */
void PrimePlot::generatePrimePlot() {

    std::string file = "Prime Distribution";
    std::string filename = "../Analysis/Distribution/primeDistribution.bmp";
    printf("\nAttempting to write prime distribution as SVG.\n");

    filename = "../Analysis/Distribution/primeDistribution.svg";
    std::ofstream outfile;
    outfile.open(filename);

    int outputWidth = 1200, outputHeight = 1200;
    float radius = 2.0f;

    headerSVG(outfile, outputWidth, outputHeight, file);

    int limit = 100000;
    for (int i = 0; i < limit; i++) {

        if (isPrime(i)) {
            float currX = 100 + (limit + i * cos(i)) / 200.0f;
            float currY = 100 + (limit + i * sin(i)) / 200.0f;

            outfile << "    <circle cx=\"" << currX << "\" cy=\"" << currY << "\" r=\"" << radius << "\" fill=\"rgb(0,0,0)\" id=\"circle" << i << "\"/>\n";
        } else {
            float currX = 100 + (limit + i * cos(i)) / 200.0f;
            float currY = 100 + (limit + i * sin(i)) / 200.0f;

            outfile << "    <circle cx=\"" << currX << "\" cy=\"" << currY << "\" r=\"" << radius << "\" fill=\"rgb(255,255,255)\" id=\"circle" << i << "\"/>\n";
        }
    }

    // Draw Cartesian gridlines
    outfile << "    <line x1=\"100\" y1=\"600\" x2=\"1100\" y2=\"600\" stroke=\"black\" />";        // X Axis
    outfile << "    <line x1=\"600\" y1=\"100\" x2=\"600\" y2=\"1100\" stroke=\"black\" />";        // Y Axis
    outfile << "    <line x1=\"100\" y1=\"100\" x2=\"100\" y2=\"1100\" stroke=\"black\" />";        // Left
    outfile << "    <line x1=\"1100\" y1=\"100\" x2=\"1100\" y2=\"1100\" stroke=\"black\" />";      // Right
    outfile << "    <line x1=\"100\" y1=\"1100\" x2=\"1100\" y2=\"1100\" stroke=\"black\" />";      // Bottom
    outfile << "    <line x1=\"100\" y1=\"100\" x2=\"1100\" y2=\"100\" stroke=\"black\" />";        // Top

    // Draw tickmarks
    //outfile << "    <line x1=\"350\" y1=\"100\" x2=\"350\" y2=\"1100\" stroke=\"black\" stroke-dasharray=\"10,10\" />";        // Left
    //outfile << "    <line x1=\"850\" y1=\"100\" x2=\"850\" y2=\"1100\" stroke=\"black\" stroke-dasharray=\"10,10\" />";        // Right
    //outfile << "    <line x1=\"100\" y1=\"350\" x2=\"1100\" y2=\"350\" stroke=\"black\" stroke-dasharray=\"10,10\" />";        // Bottom
    //outfile << "    <line x1=\"100\" y1=\"850\" x2=\"1100\" y2=\"850\" stroke=\"black\" stroke-dasharray=\"10,10\" />";        // Top

    // Draw polar gridlines
    /*outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 500 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" stroke-dasharray=\"25,25\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 375 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" stroke-dasharray=\"25,25\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 250 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" stroke-dasharray=\"25,25\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 125 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" stroke-dasharray=\"25,25\" id=\"circle100001\" />\n";*/
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 500 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 375 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 250 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 << "\" cy=\"" << 600 << "\" r=\"" << 125 << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";

    // Axis labels
    //outfile << "<text x=\"50\" y=\"600\" class=\"small\">180&#xb0;</text>";              // Left
    //outfile << "<text x=\"1150\" y=\"600\" class=\"small\">0&#xb0;</text>";             // Right
    //outfile << "<text x=\"600\" y=\"50\" class=\"small\">90&#xb0;</text>";              // Top
    //outfile << "<text x=\"600\" y=\"1150\" class=\"small\">270&#xb0;</text>";            // Bottom

    footerSVG(outfile);
    outfile.close();

    filename = "../Analysis/Distribution/primeDistribution.SVG";
    printf("    SVG written: %s\n", filename.c_str());
    printf("Successfully wrote prime distribution as SVG.\n");
}