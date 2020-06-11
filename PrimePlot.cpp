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
 * Generates prime plot as SVG.
 */
void PrimePlot::generatePrimePlot() {

    std::string file = "Prime Distribution";
    std::string filename = "../Analysis/Distribution/primeDistribution.bmp";
    printf("\nAttempting to write prime distribution as SVG.\n");

    filename = "../Analysis/Distribution/primeDistribution.svg";
    std::ofstream outfile;
    outfile.open(filename);

    int initialWidth = 1000, initialHeight = 1000;
    int marginX = 200, marginY = 200;
    int scaleFactor = 4.0f;
    int outputWidth = (initialWidth + marginX) / scaleFactor, outputHeight = (initialHeight + marginY) / scaleFactor;
    float radius = 0.25f;

    headerSVG(outfile, outputWidth, outputHeight, file);

    int limit = 50000;
    float limitFactor = 0.002f;

    for (int i = 0; i < limit; i++) {

        if (isPrime(i)) {
            float currX = ((marginX / 2) + (limit + i * cos(i)) / (float)(limit * limitFactor)) / scaleFactor;
            float currY = ((marginY / 2) + (limit - i * sin(i)) / (float)(limit * limitFactor)) / scaleFactor;

            float factor = (float)i / (float)limit;

            // Blue gradient
            /*int r = 0 + 134 * factor;
            int g = 83 + 136 * factor;
            int b = 95 + 137 * factor;*/

            // Green-blue gradient
            /*int r = 67 - 42 * factor;
            int g = 198 - 170 * factor;
            int b = 172 - 88 * factor;*/

            // Black
            int r = 0;
            int g = 0;
            int b = 0;

            // Create RGB string
            std::string rgb = "rgb(";
            rgb += std::to_string(r);
            rgb += ",";
            rgb += std::to_string(g);
            rgb += ",";
            rgb += std::to_string(b);
            rgb += ")";

            outfile << "    <circle cx=\"" << currX << "\" cy=\"" << currY << "\" r=\"" << radius << "\" fill=\"" << rgb << "\" stroke=\"" << rgb << "\" id=\"circle" << i << "\"/>\n";
        }
    }

    // Draw Cartesian gridlines
    /*outfile << "    <line x1=\"100\" y1=\"600\" x2=\"1100\" y2=\"600\" stroke=\"black\" />";        // X Axis
    outfile << "    <line x1=\"600\" y1=\"100\" x2=\"600\" y2=\"1100\" stroke=\"black\" />";        // Y Axis
    outfile << "    <line x1=\"100\" y1=\"100\" x2=\"100\" y2=\"1100\" stroke=\"black\" />";        // Left
    outfile << "    <line x1=\"1100\" y1=\"100\" x2=\"1100\" y2=\"1100\" stroke=\"black\" />";      // Right
    outfile << "    <line x1=\"100\" y1=\"1100\" x2=\"1100\" y2=\"1100\" stroke=\"black\" />";      // Bottom
    outfile << "    <line x1=\"100\" y1=\"100\" x2=\"1100\" y2=\"100\" stroke=\"black\" />";        // Top*/
    outfile << "    <line x1=\"25\" y1=\"150\" x2=\"275\" y2=\"150\" stroke=\"black\" />";        // X Axis
    outfile << "    <line x1=\"150\" y1=\"25\" x2=\"150\" y2=\"275\" stroke=\"black\" />";        // Y Axis
    outfile << "    <line x1=\"25\" y1=\"25\" x2=\"25\" y2=\"275\" stroke=\"black\" />";        // Left
    outfile << "    <line x1=\"275\" y1=\"25\" x2=\"275\" y2=\"275\" stroke=\"black\" />";      // Right
    outfile << "    <line x1=\"25\" y1=\"275\" x2=\"275\" y2=\"275\" stroke=\"black\" />";      // Bottom
    outfile << "    <line x1=\"25\" y1=\"25\" x2=\"275\" y2=\"25\" stroke=\"black\" />";        // Top

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
    outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 500 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 375 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 250 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 125 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";

    // Polar axis labels
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"12.5\" y=\"150\" font-size=\"10px\">180&#xb0;</text>";              // Left
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"287.5\" y=\"150\" font-size=\"10px\">0&#xb0;</text>";             // Right
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"150\"  y=\"12.5\" font-size=\"10px\">90&#xb0;</text>";              // Top
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"150\" y=\"287.5\" font-size=\"10px\">270&#xb0;</text>";            // Bottom

    // Polar axis radius labels
    //outfile << "<text font-family=\"Times, serif\" fill=\"blue\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"181.25\" y=\"181.25\" font-size=\"10px\">2500</text>";            // tick right 1
    //outfile << "<text font-family=\"Times, serif\" fill=\"blue\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"212.5\" y=\"212.5\" font-size=\"10px\">5000</text>";            // tick right 2
    //outfile << "<text font-family=\"Times, serif\" fill=\"blue\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"243.75\" y=\"243.75\" font-size=\"10px\">7500</text>";            // tick right 3

    footerSVG(outfile);
    outfile.close();

    filename = "../Analysis/Distribution/primeDistribution.SVG";
    printf("    SVG written: %s\n", filename.c_str());
    printf("Successfully wrote prime distribution as SVG.\n");
}

/*
 * Generate primes along unit circle as SVG.
 */
void PrimePlot::generateUnitCircle() {

    std::string file = "Prime Unit Circle Distribution";
    printf("\nAttempting to write prime unit circle distribution as SVG.\n");

    std::string filename = "../Analysis/Distribution/primeUnitCircle.svg";
    std::ofstream outfile;
    outfile.open(filename);

    int initialWidth = 1000, initialHeight = 1000;
    int marginX = 200, marginY = 200;
    int scaleFactor = 4.0f;
    int outputWidth = (initialWidth + marginX) / scaleFactor, outputHeight = (initialHeight + marginY) / scaleFactor;
    float radius = 1.0f;

    headerSVG(outfile, outputWidth, outputHeight, file);

    int current = 2;
    int count = 0;
    int numPrimes = 256;

    // Loop until numPrimes is reached
    while (count < numPrimes) {

        if (isPrime(current) || current == 2 || current == 3) {

            float currX = ((marginX / 2) + (500 + cos(current) * 475)) / 4.0f;
            float currY = ((marginY / 2) + (500 - sin(current) * 475)) / 4.0f;

            int degrees = (int)floor(current * 180.0f / 3.14159f) % 360;

            float factor = (float)degrees / 360.0f;

            // Blue gradient
            /*int r = 0 + 134 * factor;
            int g = 83 + 136 * factor;
            int b = 95 + 137 * factor;*/

            // Green-blue gradient
            int r = 67 - 42 * factor;
            int g = 198 - 170 * factor;
            int b = 172 - 88 * factor;

            // Black
            /*int r = 0;
            int g = 0;
            int b = 0;*/

            // Create RGB string
            std::string rgb = "rgb(";
            rgb += std::to_string(r);
            rgb += ",";
            rgb += std::to_string(g);
            rgb += ",";
            rgb += std::to_string(b);
            rgb += ")";

            outfile << "    <circle cx=\"" << currX << "\" cy=\"" << currY << "\" r=\"" << radius << "\" fill=\"" << rgb << "\" stroke=\"" << rgb << "\" id=\"circle" << count++ << "\"/>\n";

            printf("Current Prime: %d\n", current);
        }

        current++;
    }

    // Draw Cartesian gridlines
    /*outfile << "    <line x1=\"100\" y1=\"600\" x2=\"1100\" y2=\"600\" stroke=\"black\" />";        // X Axis
    outfile << "    <line x1=\"600\" y1=\"100\" x2=\"600\" y2=\"1100\" stroke=\"black\" />";        // Y Axis
    outfile << "    <line x1=\"100\" y1=\"100\" x2=\"100\" y2=\"1100\" stroke=\"black\" />";        // Left
    outfile << "    <line x1=\"1100\" y1=\"100\" x2=\"1100\" y2=\"1100\" stroke=\"black\" />";      // Right
    outfile << "    <line x1=\"100\" y1=\"1100\" x2=\"1100\" y2=\"1100\" stroke=\"black\" />";      // Bottom
    outfile << "    <line x1=\"100\" y1=\"100\" x2=\"1100\" y2=\"100\" stroke=\"black\" />";        // Top*/
    outfile << "    <line x1=\"25\" y1=\"150\" x2=\"275\" y2=\"150\" stroke=\"black\" />";        // X Axis
    outfile << "    <line x1=\"150\" y1=\"25\" x2=\"150\" y2=\"275\" stroke=\"black\" />";        // Y Axis
    outfile << "    <line x1=\"25\" y1=\"25\" x2=\"25\" y2=\"275\" stroke=\"black\" />";        // Left
    outfile << "    <line x1=\"275\" y1=\"25\" x2=\"275\" y2=\"275\" stroke=\"black\" />";      // Right
    outfile << "    <line x1=\"25\" y1=\"275\" x2=\"275\" y2=\"275\" stroke=\"black\" />";      // Bottom
    outfile << "    <line x1=\"25\" y1=\"25\" x2=\"275\" y2=\"25\" stroke=\"black\" />";        // Top

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
    outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 475 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    //outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 375 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    //outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 250 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";
    //outfile << "    <circle cx=\"" << 600 / scaleFactor << "\" cy=\"" << 600 / scaleFactor << "\" r=\"" << 125 / scaleFactor << "\" stroke=\"black\" opacity=\"0.5\" fill=\"none\" id=\"circle100001\" />\n";

    // Polar axis labels
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"12.5\" y=\"150\" font-size=\"10px\">180&#xb0;</text>";              // Left
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"287.5\" y=\"150\" font-size=\"10px\">0&#xb0;</text>";             // Right
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"150\"  y=\"12.5\" font-size=\"10px\">90&#xb0;</text>";              // Top
    outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"150\" y=\"287.5\" font-size=\"10px\">270&#xb0;</text>";            // Bottom

    // Polar axis radius labels
    //outfile << "<text font-family=\"Times, serif\" fill=\"blue\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"181.25\" y=\"181.25\" font-size=\"10px\">2500</text>";            // tick right 1
    //outfile << "<text font-family=\"Times, serif\" fill=\"blue\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"212.5\" y=\"212.5\" font-size=\"10px\">5000</text>";            // tick right 2
    //outfile << "<text font-family=\"Times, serif\" fill=\"blue\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"243.75\" y=\"243.75\" font-size=\"10px\">7500</text>";            // tick right 3

    footerSVG(outfile);
    outfile.close();

    filename = "../Analysis/Distribution/primeUnitCircle.SVG";
    printf("    SVG written: %s\n", filename.c_str());
    printf("Successfully wrote prime unit circle distribution as SVG.\n");
}