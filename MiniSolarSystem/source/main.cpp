#include "repch.h"
#include "Scene.h"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define SCREENWIDTH 1280
#define SCREENHEIGHT 800

int main()
{	
	if (!glfwInit())
	{
		std::cout << "GLFW Init Failed!" << std::endl;
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	GLFWwindow* window = glfwCreateWindow(SCREENWIDTH, SCREENHEIGHT, "Mini Solar System", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Failed!" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		// Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Enable depth buffer
		glEnable(GL_DEPTH_TEST);

		// Init ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

		double currentFrame = 0, lastFrame = 0;
		float deltaTime;

		// Create Scene
		std::unique_ptr<Scene> scene = std::make_unique<Scene>();
		scene->Init();

		while (!glfwWindowShouldClose(window))
		{
			// ImGui Newframe
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// Calculate deltatime
			currentFrame = glfwGetTime();
			deltaTime = static_cast<float>(currentFrame - lastFrame);
			lastFrame = currentFrame;

			// Update Scene
			scene->Update(deltaTime, *window);

			// Draw ImGui
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	// Destroy ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Destroy window and exit application
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}